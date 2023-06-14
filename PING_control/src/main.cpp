/*
ce code doit être uploadé sur l'esp32 du plateau de jeu
*/

#include <Arduino.h>
#include "Ping.hpp"

PING the_ping;
// for Serial reading
#define CODE_BP_DROIT 0
#define CODE_BP_GAUCHE 1
#define CODE_BP_SHOOT 2
#define CODE_BP_THROW_IN 3

#define CODE_PUSH 0
#define CODE_RELEASE 1

// for Serial writing
#define CODE_GOAL 0

#define SEP ";"

void receiveFromSerial()
{
  // si on recoit des données sur le port serie depuis l'esp32 web
  if (Serial.available())
  {

    String data = Serial.readStringUntil('\n'); // de la forme "1;0;1" ou "1;1;1"
    String player_id = data.substring(0, data.indexOf(SEP));
    Player *player = the_ping.getPlayer(player_id.toInt());

    if (!the_ping.isReadToPlay())
      return;

    // on choisi l'action a effectuer en fonction du code boutton et si on le push ou release
    switch (data.substring(data.indexOf(SEP) + 1).toInt())
    {
    case CODE_BP_DROIT:
      if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
      {
        player->right();
      }
      else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
      {
        player->stop();
      }
      break;
    case CODE_BP_GAUCHE:
      if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
      {
        player->left();
      }
      else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
      {
        player->stop();
      }
      break;
    case CODE_BP_SHOOT:
      if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_PUSH)
      {
        player->shoot();
      }
      else if (data.substring(data.indexOf(SEP) + 3).toInt() == CODE_RELEASE)
      {
        player->release();
      }
      break;

    case CODE_BP_THROW_IN:
      // remise en jeu
      the_ping.throwIn();
      break;
    default:
      break;
    }
  }
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

    if (!the_ping.checkIsBallIn())
      continue;

    if (the_ping.waittingForThrowIn())
      continue;

    if (!the_ping.isBallInStateChange())
      continue;


    if (!the_ping.isReadToPlay())
      {
        continue;
      }

    // si on arrive ici, c'est que la balle vient d'etre mise dans un des joueurs

    the_ping.waitForThrowIn(); // on stop tous les joueurs

    uint8_t player_id = the_ping.getPlayerIdWichHasTheBallIn();
    String player_id_str = String(player_id);
    String data = player_id_str + SEP + CODE_GOAL;
    Serial.println(data);
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
  Serial.setTimeout(50);
  the_ping.init();
  // AsynTask on the Second core

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
  // Serial.print("analogRead(PHOTODIOD_PIN_1) :"+String(analogRead(PHOTODIOD_PIN_1))+"   ");
  // Serial.print("analogRead(PHOTODIOD_PIN_2) :"+String(analogRead(PHOTODIOD_PIN_2))+"   ");
  // Serial.print("analogRead(PHOTODIOD_PIN_3) :"+String(analogRead(PHOTODIOD_PIN_3))+"   ");
  // Serial.println("analogRead(PHOTODIOD_PIN_4) :"+String(analogRead(PHOTODIOD_PIN_4)));
  // delay(50);
}