#include "webConnection.hpp"

#define DEBUG false

int MyWebServer::initGamePage()
{
    initGetLivesRequest();
    initGetLives_SSE();
    playerActionRequest();
    initGoalTakenSSE();
    initGetEndGameSSE();
    return 0;
}

void MyWebServer::initGetLivesRequest()
{
    server->on("/getLives", HTTP_GET, [this](AsyncWebServerRequest *request)
    {
        //on verifie que le paramètre "playerId" est bien présent
        if (!request->hasParam("playerId"))
        {
            request->send(400, "text/plain", "player id is missing");
            return;
        }
        //on récupere le paramètre "playerId" de la requete
        String playerId = request->getParam("playerId")->value();
        if (DEBUG)
            Serial.println("getLives request received for player " + playerId);

        //on envoie la réponse
        request->send(200, "text/plain", String(playerLives[playerId.toInt()]));
    });
}

void MyWebServer::initGetLives_SSE()
{
    getLives_SSE_0 = new AsyncEventSource("/getLives_SSE_0");
    initGetLives_spesific_SSE(*getLives_SSE_0);
    getLives_SSE_1 = new AsyncEventSource("/getLives_SSE_1");
    initGetLives_spesific_SSE(*getLives_SSE_1);
    getLives_SSE_2 = new AsyncEventSource("/getLives_SSE_2");
    initGetLives_spesific_SSE(*getLives_SSE_2);
    getLives_SSE_3 = new AsyncEventSource("/getLives_SSE_3");
    initGetLives_spesific_SSE(*getLives_SSE_3);
}

void MyWebServer::initGetLives_spesific_SSE(AsyncEventSource &sse)
{
    sse.onConnect([](AsyncEventSourceClient *client)
                  {
                      if (DEBUG)
                          Serial.println("Client connected to GetLives SSE");
                      // Code à exécuter lorsque le client se connecte
                  });
    // Ajouter l'événement au serveur
    server->addHandler(&sse);
}

void MyWebServer::initGetEndGameSSE()
{
    getEndGame_SSE = new AsyncEventSource("/getEndGame_SSE");
    getEndGame_SSE->onConnect([](AsyncEventSourceClient *client)
                              {
                                  if (DEBUG)
                                      Serial.println("Client connected to getEndGameSSE");
                                  // Code à exécuter lorsque le client se connecte
                              });
    // Ajouter l'événement au serveur
    server->addHandler(getEndGame_SSE);
}

void MyWebServer::initGoalTakenSSE()
{
    getGoalTaken_SSE = new AsyncEventSource("/getGoalTaken_SSE");
    getGoalTaken_SSE->onConnect([](AsyncEventSourceClient *client)
                                {
                                    if (DEBUG)
                                        Serial.println("Client connected to goalTakenSSE");
                                    // Code à exécuter lorsque le client se connecte
                                });
    // Ajouter l'événement au serveur
    server->addHandler(getGoalTaken_SSE);
}

bool MyWebServer::isPlayerAction(String str)
{
    return (str == LEFT) || (str == RIGHT) || (str == STOP) || (str == PUNCH) || (str == STOP_PUNCH) || (str == RESUME);
}

void MyWebServer::playerActionRequest()
{
    server->on(PLAYER_ACTION_REQUEST, HTTP_GET, [this](AsyncWebServerRequest *request)
               {
            if (DEBUG)
                Serial.println("Player Action Request: "+request->url());
            // Code à exécuter lorsque le client se connecte
            //on récupère les paramètres
            // long player = request->getParam("playerId")->value().toInt();
            // String action = request->getParam("action")->value();

            if(!request->hasParam("playerId"))
                request->send(200, "text/plain", "missing playerId arg");
            
            if(!request->hasParam("action"))
                request->send(200, "text/plain", "missing action arg");

            long player = request->getParam("playerId")->value().toInt();
            String action = request->getParam("action")->value();

            // on verifie l'integrité des paramètres
            if (player < 0 || player > 3)
            {
                if (DEBUG)
                    Serial.println("Player Action Request: playerId out of range");
                request->send(400, "text/plain", "Bad playerId");
                return;
            }
            if (!this->isPlayerAction(action))
            {
                if (DEBUG)
                    Serial.println("Player Action Request: action not recognized");
                request->send(400, "text/plain", "Bad action");
                return;
            }
            // on envoie toute la requête au serial
            toSendToSerial += String(PLAYER_ACTION_REQUEST) + "?playerId=" + String(player) + "&action=" + action + "\n";
            request->send(200, "text/plain", "OK"); });
}