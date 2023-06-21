/*
ce code doit être uploadé sur l'esp32 du plateau de jeu
*/

#include <Arduino.h>
#include "Ping.hpp"

PING the_ping;
// for Serial reading
// player actions
#define LEFT "left"
#define RIGHT "right"
#define STOP "stop"
#define PUNCH "punch"
#define STOP_PUNCH "stop-punch"
#define RESUME "resume"

// for Serial writing
#define CODE_GOAL "/goalTaken" // /goalTaken?playerId="id"

#define SEP ";"

//#define DEBUG
void receiveFromSerial()
{
  // si on recoit des données sur le port serie depuis l'esp32 web
  if (Serial.available())
  {

    if (!the_ping.isReadToPlay())
    {
      return;
    }

    String data = Serial.readStringUntil('\n') + '\n'; // de la forme /playerAction?playerId="id"&action="action"

#ifdef DEBUG
    Serial.print("data : ");
    Serial.println(data);
#endif
    // on verifie que le message est bien du type /playerAction
    String dataType = data.substring(0, data.indexOf("?"));
    if (dataType != "/playerAction")
    {
      return;
    }
    // on recupere l'id du joueur
    String playerId = data.substring(data.indexOf("playerId=") + 9, data.indexOf("&"));
    // on recupere l'action
    String action = data.substring(data.indexOf("action=") + 7, data.indexOf("\n"));

    int player_id_int = playerId.toInt()+1;

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
      Serial.print("error action");
#endif
    }
  }
}
//   String player_id = data.substring(0, data.indexOf(SEP));
//   Player *player = the_ping.getPlayer(player_id.toInt());

//   if (!the_ping.isReadToPlay())
//     return;

//   // on choisi l'action a effectuer en fonction du code boutton et si on le push ou release
//   switch (data.substring(data.indexOf(SEP) + 1).toInt())
//   {
//   case CODE_BP_DROIT:
//     if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
//     {
//       player->right();
//     }
//     else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
//     {
//       player->stop();
//     }
//     break;
//   case CODE_BP_GAUCHE:
//     if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
//     {
//       player->left();
//     }
//     else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
//     {
//       player->stop();
//     }
//     break;
//   case CODE_BP_SHOOT:
//     if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
//     {
//       player->shoot();
//     }
//     else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
//     {
//       player->release();
//     }
//     break;

//   case CODE_BP_THROW_IN:
//     // remise en jeu
//     Serial.println("remise en jeu");
//     the_ping.throwIn();
//     break;
//   default:
//     break;
//   }
// }

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

    if (the_ping.waittingForThrowIn())
      continue;

    if (!the_ping.checkIsBallIn())
      continue;

    if (!the_ping.isBallInStateChange())
      continue;

    if (!the_ping.isReadToPlay())
    {
      continue;
    }

    // si on arrive ici, c'est que la balle vient d'etre mise dans un des joueurs

    the_ping.waitForThrowIn(); // on stop tous les joueurs
    uint8_t player_id = the_ping.getPlayerIdWichHasTheBallIn()-1;
    String player_id_str = String(player_id);
    Serial.println(String(CODE_GOAL) + "?playerId=" + player_id_str);
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