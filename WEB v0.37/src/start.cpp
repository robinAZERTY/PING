#include "webConnection.hpp"

int MyWebServer::initStartGameRequest()
{
    startGameRequest();
    return 0;
}

void MyWebServer::startGameRequest()
{
    server->on("/startGame", HTTP_GET, [this](AsyncWebServerRequest * request)
        {
            //on regarde la présence du paramètre gameMode
            if(!request->hasParam("gameMode"))
                request->send(400, "text/plain", "missing gameMode arg");

            gameMode = request->getParam("gameMode")->value();

            
            this->started=true;
            if(DEBUG)
                Serial.println("StartGame request:"+request->url()+"?gameMode=" +request->getParam("gameMode")->value() + ", response:"+" ok");
            
            //send to all connected player that the game has started
            String toSend = "/gameStarted?gameMode="+gameMode;
            SSE->send(toSend.c_str(),NULL,millis(),100);
            //send to the serial port the startGame request
            toSendToSerial += ("/startGame?playerList=" + constructPlayerList()+"\n");
            request->send(200,"text/plain","ok");
        }
    );
}
