#include <Arduino.h>
#include "percutor.hpp"

float power = 0.0;
percutor p1(4, &power);
unsigned long time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {

  //update power on the serial monitor
  if (Serial.available())
  {
    power = Serial.parseFloat();
    Serial.print("power = ");
    Serial.println(power);
    if (power > 1.0)
    {
      power = 1.0;
    }
    else if (power < 0.0)
    {
      power = 0.0;
    }
  }

  time = millis();
  p1.update(time);
}