#include <Arduino.h>
#include "Ping.hpp"

PING the_ping;
void Task1func()
{
  // using the serial monitor to control the player
  //  on press left arrow key -> move left
  //  on release left arrow key -> stop
  //  on press right arrow key -> move right
  //  on release right arrow key -> stop
  //  on press space bar -> shoot
  //  on release space bar -> release
  // the key datas are sent by the python script on the serial port

  // if a entier new line was printed
  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');        //"654654,54"
    String key = data.substring(0, data.indexOf(',')); //"654654"
    String ty = data.substring(data.indexOf(',') + 1); //"54"

    if (key == "1073741904") // left arrow key
    {
      if (ty == "768") // press
      {
        the_ping.player1.left();
        the_ping.player2.left();
        the_ping.player3.left();
        the_ping.player4.left();
        }
      else if (ty == "769") // release
      {
        the_ping.player1.stop();
        the_ping.player2.stop();
        the_ping.player3.stop();
        the_ping.player4.stop();
      }
    }
    else if (key == "1073741903") // right arrow key
    {
      if (ty == "768") // press
      {
        the_ping.player1.right();
        the_ping.player2.right();
        the_ping.player3.right();
        the_ping.player4.right();
      }
      else if (ty == "769") // release
      {
        the_ping.player1.stop();
        the_ping.player2.stop();
        the_ping.player3.stop();
        the_ping.player4.stop();
      }
    }
    else if (key == "32") // space bar
    {
      if (ty == "768") // press
      {
        the_ping.player1.shoot();
        the_ping.player2.shoot();
        the_ping.player3.shoot();
        the_ping.player4.shoot();
      }
      else if (ty == "769") // release
      {
        the_ping.player1.release();
        the_ping.player2.release();
        the_ping.player3.release();
        the_ping.player4.release();
        
      }
    }
  }
}

void Task2func()
{
  the_ping.play();
}

void AsyncFunc(void *pvParameters)
{
  while(true)
  {
  the_ping.isBallIn();
  delay(10);
  }
}
TaskHandle_t AsyncTask;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  the_ping.init();
// AsynTask on the Second core
  xTaskCreatePinnedToCore(
      AsyncFunc, /* Function to implement the task */
      "AsyncTask",   /* Name of the task */
      10000,     /* Stack size in words */
      NULL,      /* Task input parameter */
      0,         /* Priority of the task */
      &AsyncTask,    /* Task handle. */
      0);        /* Core where the task should run */

}
  
void loop()
{  
Task1func();//on regarde sur le port serie si on a recu des commandes et on execute les commandes
Task2func();
}