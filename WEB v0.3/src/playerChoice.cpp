#include "webConnection.hpp"

#define DEBUG true

int MyWebServer::initPlayerChoice()
{
    playerChoiceRequest();
    initConnectedPlayerSSE();
    playerDisplayRequest();
    // sendPlayerAvailability();
    // sendPlayerAvailability_SSE();

    return 0;
}

void MyWebServer::initConnectedPlayerSSE()
{
    connectedPlayerSSE = new AsyncEventSource("/getConnectedPlayerSSE");
    // Définir la fonction de gestion de l'événement "connect"
    connectedPlayerSSE->onConnect([](AsyncEventSourceClient *client)
                     {
                         if (DEBUG)
                             Serial.println("Client connected to SSE");
                         // Code à exécuter lorsque le client se connecte
                     });
    // Ajouter l'événement au serveur
    server->addHandler(connectedPlayerSSE);
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
            connectedPlayerSSE->send(constructPlayerList().c_str(),NULL,millis(),100);
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
            connectedPlayerSSE->send(constructPlayerList().c_str(),NULL,millis(),100);
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

// void MyWebServer::sendPlayerAvailability()
// {
//     server->on("/getPlayerAvailability", HTTP_GET, [this](AsyncWebServerRequest *request)
//                {
//         String toSend="";
//         for(uint i=0;i<4;i++)
//         {
//             if(this->connectedPlayer[i])
//                 toSend+="1";
//             else
//                 toSend+="0";
//         }
//         if (DEBUG)
//             Serial.println("Sending: "+toSend);
//         request->send(200,"text/plain",toSend); });
// }

// void MyWebServer::sendPlayerAvailability_SSE()
// {
//     if (DEBUG)
//         Serial.println("Creating event source");
//     event = new AsyncEventSource("/getPlayerAvailability_SSE");

//     if (DEBUG)
//         Serial.println("Setting up event source");
//     event->onConnect([this](AsyncEventSourceClient *client)
//                      {

//                         if (DEBUG)
//                             Serial.println("Client connected");

//                         //check if connectedPlayer and previousConnectedPlayer are the same
//                         bool changed=false;
//                         for(uint i=0;i<4;i++)
//                         {
//                             if(this->connectedPlayer[i]!=this->previousConnectedPlayer[i])
//                             {
//                                 changed=true;
//                                 previousConnectedPlayer[i]=connectedPlayer[i];
//                             }
//                         }
//                         if (!changed)
//                             return;

//                         String toSend="";
//                         for(uint i=0;i<4;i++)
//                         {
//                             if(this->connectedPlayer[i])
//                                 toSend+="1";
//                             else
//                                 toSend+="0";
//                         }
//                         if (DEBUG)
//                             Serial.println("Sending: "+toSend);

//                         client->send(toSend.c_str(),NULL,millis(),100); });

//     server->addHandler(event);
// }
