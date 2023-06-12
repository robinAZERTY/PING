#include <Arduino.h>
#include "Ping.hpp"

PING the_ping;

#define CODE_BP_DROIT 0
#define CODE_BP_GAUCHE 1
#define CODE_BP_SHOOT 2

#define CODE_PUSH 0
#define CODE_RELEASE 1

#define SEP ";"

void receiveFromSerial()
{
  if (Serial.available())
  {

    String data = Serial.readStringUntil('\n'); // de la forme "1;0;1" ou "1;1;1"
    String player_id = data.substring(0, data.indexOf(SEP));
    Player *player = NULL;
    switch (player_id.toInt())
    {
    case 1:
      player = &the_ping.player1;
      break;
    case 2:
      player = &the_ping.player2;
      break;
    case 3:
      player = &the_ping.player3;
      break;
    case 4:
      player = &the_ping.player4;
      break;
    }
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
    }
  }
}

TaskHandle_t Task1,Task2, Task3;

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
    the_ping.isBallIn();
    delay(10);
  }
}

void play_Task(void *pvParameters)
{
  while (true)
  {
    the_ping.play();
    delay(10);
  }
}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  the_ping.init();
  // AsynTask on the Second core
  xTaskCreatePinnedToCore(
      receiveFromSerial_Task, /* Function to implement the task */
      "receiveFromSerial_Task", /* Name of the task */
      10000,                    /* Stack size in words */
      NULL,                     /* Task input parameter */
      0,                        /* Priority of the task */
      &Task1,               /* Task handle. */
      0);                       /* Core where the task should run */
  
  xTaskCreatePinnedToCore(
      lookForBallIn_Task, /* Function to implement the task */
      "lookForBallIn_Task", /* Name of the task */
      10000,                    /* Stack size in words */
      NULL,                     /* Task input parameter */
      1,                        /* Priority of the task */
      &Task2,               /* Task handle. */
      0);                       /* Core where the task should run */
    
  

}

void loop()
{
  the_ping.play();
}