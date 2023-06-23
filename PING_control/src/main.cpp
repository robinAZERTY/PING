/*
ce code doit être uploadé sur l'esp32 du plateau de jeu
*/

#include <Arduino.h>
#include "Ping.hpp"

PING the_ping;
// for Serial reading
#define PLAYER_ACTION "/playerAction" // /playerAction?playerId="id"&action="action"
#define PLAYER_ID "playerId="         // param
#define ACTION "action="              // param
#define LEFT "left"                   // value
#define RIGHT "right"
#define STOP "stop"
#define PUNCH "punch"
#define STOP_PUNCH "stop-punch"
#define RESUME "resume"

#define GAME_STARTED "/startGame" // /startGame?playerList="1010"
#define PLAYER_LIST "playerList=" // param

// for Serial writing
#define CODE_GOAL "/goalTaken" // /goalTaken?playerId="id"

#define DEBUG

void dealWithPlayerAction(String requestType, String entierRequest)
{
  if (requestType != PLAYER_ACTION)
    return;

  // on recupere l'id du joueur
  String playerId = entierRequest.substring(entierRequest.indexOf(PLAYER_ID) + 9, entierRequest.indexOf("&"));
  // on recupere l'action
  String action = entierRequest.substring(entierRequest.indexOf(ACTION) + 7, entierRequest.indexOf("\n"));

  int player_id_int = playerId.toInt() + 1;

#ifdef DEBUG
  Serial.print("player_id_int : ");
  Serial.println(player_id_int);
  Serial.print("action : ");
  Serial.println(action);
#endif

  // on verifie la validité de l'id
  if (player_id_int < 1 || player_id_int > 4)
  {
#ifdef DEBUG
    Serial.print("error id");
#endif
    return;
  }

  // on recupere le joueur
  Player *player = the_ping.getPlayer(player_id_int);
  // on verifie que le joueur est bien en jeu
  if (!player->isPlaying())
  {
#ifdef DEBUG
    Serial.println("error this player is not in playing");
#endif
    return;
  }

  if (action == LEFT)
    player->left();
  else if (action == RIGHT)
    player->right();
  else if (action == STOP)
    player->stop();
  else if (action == PUNCH)
    player->shoot();
  else if (action == STOP_PUNCH)
    player->release();
  else if (action == RESUME)
    the_ping.throwIn();
  else
  {
#ifdef DEBUG
    Serial.println("error action");
#endif
  }
}

void dealWithStartGame(String requestType, String entierRequest)
{
  if (requestType != GAME_STARTED)
    return;

  // on recupere la liste des joueurs
  String playerList = entierRequest.substring(entierRequest.indexOf(PLAYER_LIST) + 11, entierRequest.indexOf("\n"));

#ifdef DEBUG
  Serial.print("playerList : ");
  Serial.println(playerList);
#endif

  // on verifie la validité de la liste
  if (playerList.length() != 4)
  {
#ifdef DEBUG
    Serial.println("error playerList");
#endif
    return;
  }

  // on recupere le joueur
  for (int i = 0; i < 4; i++)
  {
    Player *player = the_ping.getPlayer(i + 1);
    if (playerList[i] == '0')
    {
      player->setIsPlaying(false);
#ifdef DEBUG
      Serial.println("player" + String(i) + " is not playing");
#endif
    }
    else if (playerList[i] == '1')
    {
      player->setIsPlaying(true);
#ifdef DEBUG
      Serial.println("player" + String(i) + " is playing");
#endif
    }
  }
}

void receiveFromSerial()
{
  // si on recoit des données sur le port serie depuis l'esp32 web
  if (!Serial.available())
    return;

  String data = Serial.readStringUntil('\n') + '\n'; // de la forme /playerAction?playerId="id"&action="action"

#ifdef DEBUG
  Serial.print("data : ");
  Serial.println(data);
#endif
  // on verifie que le message est bien du type /playerAction
  String dataType = data.substring(0, data.indexOf("?"));
  dealWithPlayerAction(dataType, data);
  dealWithStartGame(dataType, data);
}

TaskHandle_t Task1, Task2, Task3;

void receiveFromSerial_Task(void *pvParameters)
{
  while (true)
  {
    receiveFromSerial();
    delay(10);
  }
}

void lookForBallIn_Task(void *pvParameters)
{
  while (true)
  {
    delay(10);

    // if (the_ping.waittingForThrowIn())
    //   continue;

    if(the_ping.waittingForThrowIn())
      continue;
      
    int noobId = the_ping.isBallInStateChange();
    if (noobId == 0)
      continue;
  

#ifdef DEBUG
    Serial.print("goal for player : ");
    Serial.println(noobId);
#endif

    // on regarde si le joueur joue la partie
    if (!the_ping.getPlayer(noobId)->isPlaying())
      continue;

    // si on arrive ici, c'est que la balle vient d'etre mise dans un des joueurs qui est en jeu
    the_ping.waitForThrowIn(); // on stop tous les joueurs
    String player_id_str = String(noobId-1);
    Serial.println(String(CODE_GOAL) + "?" + String(PLAYER_ID) + player_id_str);
  }
}

void play_Task(void *pvParameters)
{
  while (true)
  {
    the_ping.play();
  }
}

void sonorInit_Task(void *pvParameters)
{
  the_ping.sonorInit();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(100);
  delay(1000);
  the_ping.init();
  // // AsynTask on the Second core

  xTaskCreatePinnedToCore(
      receiveFromSerial_Task,
      "receiveFromSerial_Task",
      10000,
      NULL,
      0,
      &Task1,
      0);

  xTaskCreatePinnedToCore(
      lookForBallIn_Task,
      "lookForBallIn_Task",
      10000,
      NULL,
      1,
      &Task2,
      0);

  xTaskCreatePinnedToCore(
      sonorInit_Task,
      "sonorInit_Task",
      10000,
      NULL,
      1,
      &Task3,
      1);
}

void loop()
{
  the_ping.play();
  // Serial.print("analogRead(PHOTODIOD_PIN_1):"+String(analogRead(PHOTODIOD_PIN_1))+",");
  // Serial.print("analogRead(PHOTODIOD_PIN_2):"+String(analogRead(PHOTODIOD_PIN_2))+",");
  // Serial.print("analogRead(PHOTODIOD_PIN_3):"+String(analogRead(PHOTODIOD_PIN_3))+",");
  // Serial.println("analogRead(PHOTODIOD_PIN_4):"+String(analogRead(PHOTODIOD_PIN_4)));
  // // Serial.print("digitalRead(END_STOP_PIN_1) :"+String(digitalRead(END_STOP_PIN_1))+"   ");
  // // Serial.print("digitalRead(END_STOP_PIN_2) :"+String(digitalRead(END_STOP_PIN_2))+"   ");
  // // Serial.print("digitalRead(END_STOP_PIN_3) :"+String(digitalRead(END_STOP_PIN_3))+"   ");
  // // Serial.println("digitalRead(END_STOP_PIN_4) :"+String(digitalRead(END_STOP_PIN_4)));
  // delay(50);
}