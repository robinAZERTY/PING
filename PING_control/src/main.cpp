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
        }
      else if (ty == "769") // release
      {
        the_ping.player1.stop();
      }
    }
    else if (key == "1073741903") // right arrow key
    {
      if (ty == "768") // press
      {
        the_ping.player1.right();
      }
      else if (ty == "769") // release
      {
        the_ping.player1.stop();
      }
    }
    else if (key == "32") // space bar
    {
      if (ty == "768") // press
      {
        the_ping.player1.shoot();
      }
      else if (ty == "769") // release
      {
        the_ping.player1.release();
      }
    }
  }
}

void Task2func()
{
  the_ping.player1.play();
}

TaskHandle_t Task1, Task2;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // use the 2 cores of the esp32
  


}
  
void loop()
{  
Task1func();//on regarde sur le port serie si on a recu des commandes et on execute les commandes
Task2func();
}