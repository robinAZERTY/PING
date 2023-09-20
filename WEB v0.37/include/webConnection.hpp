#ifndef WEB_CONNECTION_HPP
#define WEB_CONNECTION_HPP

#define DEBUG false

#define useLittleFS 


#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#ifndef useLittleFS
#include <SPIFFS.h>
#define FLASH_TYPE  SPIFFS
#else
#include <LittleFS.h>
#define FLASH_TYPE  LittleFS
#endif
#include "soc/rtc_wdt.h"

//player actions
#define LEFT String("left")
#define RIGHT String("right")
#define STOP String("stop")
#define PUNCH String("punch")
#define STOP_PUNCH String("stop-punch")
#define RESUME String("resume")

//request type
#define PLAYER_ACTION_REQUEST "/playerAction"
#define GET_LIVES_REQUEST "/getLives"

#define MAX_SIMULTANEOUS_REDIRECTION 1


class MyWebServer
{
    public:
        MyWebServer();
        ~MyWebServer();
        int beginServer();
        void sendToSerial(HardwareSerial &serial);
        void receiveFromSerial(HardwareSerial &serial);

    private:

        const String getContentType(const String path);
        int linkFiles();
        int linkFile(const char *url, const char *path, const char *contentType);
        int initIndex();
        int dealWithMsg(String str);
        int initPlayerChoice();
        int initWaitingPage();
        int initStartGameRequest();
        void startGameRequest();
        void playerChoiceRequest();
        void playerDisplayRequest();
        int initGamePage();
        void initGetLivesRequest();
        int initGetLivesListRequest();
        int initGetRedirectingPlayerRequest();
        String constructPlayerList();


        void playerActionRequest();
        bool isPlayerAction(String str);

        AsyncWebServer* server=NULL;
        AsyncEventSource *SSE=NULL;
        /* data */
        const char *ssid = "PING";
        const char *password = "123456789";
        const uint maxLives=5;
        bool connectedPlayer[4],previousConnectedPlayer[4];
        bool started=false,ended=false;
        uint8_t playerLives[4];

        String toSendToSerial="";
        String receivedFromSerial="";

        char**pathList;
        uint nbPath=0;
        String gameMode="classic";

        uint8_t redirectingPlayer=0;//pour eviter la surcharge du serveur
};

#endif