#include "webConnection.hpp"

int MyWebServer::initGetLivesListRequest()
{
    server->on("/getLiveList", HTTP_GET, [this](AsyncWebServerRequest *request)
               {
        String toSend = "";
        for (int i = 0; i < 4; i++)
        {
            toSend += String(this->playerLives[i]) + ",";
        }
        //on remove la derniere ,
        toSend = toSend.substring(0, toSend.length() - 1);
        if (DEBUG)
            Serial.println("LiveList request:" + request->url() + " response:" + toSend);
        request->send(200, "text/plain", toSend); });

    server->on("/resetGame", HTTP_GET, [this](AsyncWebServerRequest *request)
               {
        if (DEBUG)
            Serial.println("resetGame request:" + request->url());
        //reset des vies et des joueurs connectés
        for (int i = 0; i < 4; i++)
        {
            this->playerLives[i] = maxLives;
            this->connectedPlayer[i] = false;
            this->previousConnectedPlayer[i] = false;
        }
        this->started = false;
        this->ended = false;
        request->send(200, "text/plain", "OK"); });
    return 0;
}