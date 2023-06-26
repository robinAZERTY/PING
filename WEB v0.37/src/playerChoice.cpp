#include "webConnection.hpp"

int MyWebServer::initPlayerChoice()
{
    playerChoiceRequest();
    playerDisplayRequest();
    return 0;
}


void MyWebServer::playerDisplayRequest()
{
    server->on("/getPlayerList", HTTP_GET, [this](AsyncWebServerRequest * request)
        {
            const String toSend = constructPlayerList();
            if(DEBUG)
                Serial.println("PlayerList request:"+request->url()+" response:"+toSend);
            request->send(200,"text/plain",toSend);
        }
    );   
}

void MyWebServer::playerChoiceRequest()
{
    // on traite la requete /PlayerChoice?playerId=
    server->on("/PlayerChoice", HTTP_GET, [this](AsyncWebServerRequest *request)
               {
                uint8_t playerId = request->getParam("playerId")->value().toInt();
        if (DEBUG)
            Serial.println("PlayerChoice request:"+request->url()+"?"+request->getParam("playerId")->value());
        
        //on compte le nombre de joueur deja connecte
        uint nbPlayer=0;
        for(uint i=0;i<4;i++)
        {
            if(this->connectedPlayer[i])
                nbPlayer++;
        }

        if(nbPlayer==0)
        {      
            if (DEBUG)
                Serial.println("First player");
            this->connectedPlayer[playerId]=true;
            String toSend = "/connectedPlayersList?playerList=";
            toSend+=constructPlayerList();
            SSE->send(toSend.c_str(),NULL,millis(),100);
            request->send(200,"text/plain","first");
        }
        else if(this->connectedPlayer[playerId])
        {
            if (DEBUG)
                Serial.println("Player already connected");
            request->send(200,"text/plain","refused");
        }
        else
        {
            if (DEBUG)
                Serial.println("Player accepted");
            this->connectedPlayer[playerId]=true;
            String toSend = "/connectedPlayersList?playerList=";
            toSend+=constructPlayerList();
            SSE->send(toSend.c_str(),NULL,millis(),100);
            request->send(200,"text/plain","accepted");
        } });
}

String MyWebServer::constructPlayerList()
{
    String toSend="";
    for(uint i=0;i<4;i++)
    {
        if(this->connectedPlayer[i])
            toSend+="1";
        else
            toSend+="0";
    }
    return toSend;
}