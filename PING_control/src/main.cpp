#include <Arduino.h>
#include "solenoid.hpp"

float power = 0.0;
solenoid s1(4, &power);
unsigned long t = 0;

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

  t = millis();
  s1.update(t);
}