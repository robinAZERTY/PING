#include "webConnection.hpp"


MyWebServer myWeb;

void setup()
{
    Serial.begin(115200);
    myWeb.beginServer();
}

void loop()
{
    // transmit data to serial
    myWeb.sendToSerial(Serial);
    myWeb.receiveFromSerial(Serial);
    delay(10);
}