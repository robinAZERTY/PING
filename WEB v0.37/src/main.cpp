#include "webConnection.hpp"


MyWebServer myWeb;

void setup()
{
    Serial2.begin(115200);
    myWeb.beginServer();
}

void loop()
{
    // transmit data to serial
    myWeb.sendToSerial(Serial2);
    myWeb.receiveFromSerial(Serial2);
    delay(10);
}