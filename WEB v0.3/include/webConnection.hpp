#ifndef WEB_CONNECTION_HPP
#define WEB_CONNECTION_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

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
        void initConnectedPlayerSSE();
        void playerDisplayRequest();
        void initGoalTakenSSE();
        int initGamePage();
        void initGetLivesRequest();
        void initGetLives_SSE();
        void initGetLives_spesific_SSE(AsyncEventSource &sse);
        String constructPlayerList();

        void waitingPage_SSE();

        void playerActionRequest();
        bool isPlayerAction(String str);

        void initGetEndGameSSE();

        AsyncWebServer* server=NULL;
        AsyncEventSource* connectedPlayerSSE=NULL;
        AsyncEventSource *gameStartedSSE=NULL;
        AsyncEventSource *getLives_SSE_0=NULL,*getLives_SSE_1=NULL,*getLives_SSE_2=NULL,* getLives_SSE_3=NULL;
        AsyncEventSource *getGoalTaken_SSE=NULL;
        AsyncEventSource *getEndGame_SSE=NULL;
        /* data */
        const char *ssid = "PING";
        const char *password = "123456789";
        const uint maxLives=5;
        bool connectedPlayer[4]={false,false,false,false},previousConnectedPlayer[4]={false,false,false,false};
        bool started=false,ended=false;
        uint8_t playerLives[4];

        String toSendToSerial="";
        String receivedFromSerial="";

        char**pathList;
        uint nbPath=0;
};

#endif