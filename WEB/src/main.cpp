#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char *ssid = "esp32";
const char *password = "123456789";

#define CODE_BP_DROIT 0
#define CODE_BP_GAUCHE 1
#define CODE_BP_SHOOT 2

#define CODE_PUSH 0
#define CODE_RELEASE 1

#define SEP ";"


AsyncWebServer server(80);

bool choosenPlayer[4] = {0,0,0,0};
int randomPlayer = 1; 
String gameStarted = "0";


void setup()
{
  
  //----------------------------------------------------Serial
  Serial.begin(115200);

  //----------------------------------------------------SPIFFS
  if(!SPIFFS.begin())
  {
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    file.close();
    file = root.openNextFile();
  }

  //----------------------------------------------------WIFI
	WiFi.softAP(ssid, password);

  //----------------------------------------------------SERVER

  
  //---Général---
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  server.on("/rules.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/rules.html", "text/html");
  });

  server.on("/story.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/story.html", "text/html");
  });

  server.on("/waiting_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/waiting_page.html", "text/html");
  });

  server.on("/scores.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/scores.html", "text/html");
  });
  
  server.on("/start.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/start.html", "text/html");
  });

  //--------------------------------------------Images--------------------------------------------------------
  
  server.on("/img/robin.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/robin.png", "image/png");
  });

  server.on("/img/baptiste1.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/baptiste1.jpg", "image/png");
  });

  server.on("/img/baptiste2.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/baptiste2.jpg", "image/png");
  });

  server.on("/img/LOGO.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/LOGO.png", "image/png");
  });

  server.on("/img/simon.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/simon.jpg", "image/png");
  });

  server.on("/img/franck.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/franck.png", "image/png");
  });
  server.on("/img/thomas.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/img/thomas.png", "image/png");
  });

  

  

  //---Game---
  server.on("/game_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/game_page.html", "text/html");
  });

  server.on("/rightDown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche

    String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_DROIT);
    to_send += SEP;
    to_send += String(CODE_PUSH);
    Serial.println(to_send);

    request->send(200);
  });

  server.on("/rightUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    
    String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_DROIT);
    to_send += SEP;
    to_send += String(CODE_RELEASE);
    Serial.println(to_send);

    request->send(200);
  });


  server.on("/leftDown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    
    String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_GAUCHE);
    to_send += SEP;
    to_send += String(CODE_PUSH);
    Serial.println(to_send);
    request->send(200);
  });


    server.on("/leftUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    
       String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_GAUCHE);
    to_send += SEP;
    to_send += String(CODE_RELEASE);
    Serial.println(to_send);
    request->send(200);
  });

  server.on("/pushDown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
 
    String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_SHOOT);
    to_send += SEP;
    to_send += String(CODE_PUSH);
    Serial.println(to_send);
    request->send(200);
  });

  server.on("/pushUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    
    String to_send="";
    to_send += String(recievedPlayerId);
    to_send += SEP;
    to_send += String(CODE_BP_SHOOT);
    to_send += SEP;
    to_send += String(CODE_RELEASE);
    Serial.println(to_send);

    request->send(200);
  });

  server.on("/updateAvailablePlayers", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int playerId = message.toInt();
    //on met à jour le tableau des joueurs
    choosenPlayer[playerId-1] = 1;


  });
  server.on("/choosen-players", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on envoie chossenPlayer au client pour qu'il puisse mettre à jour son interface. Les valeurs sont séparées par des virgules
    request->send(200, "text/plain", String(choosenPlayer[0]) + String(choosenPlayer[1]) + String(choosenPlayer[2]) + String(choosenPlayer[3]));
    
  });

  server.on("/all-choosen", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if (choosenPlayer[0] == 1 && choosenPlayer[1] == 1 && choosenPlayer[2] == 1 && choosenPlayer[3] == 1 )
    {
    
      //envoie requete contenant randomPlayer et "1"
      request->send(200, "text/plain", "1" + String(randomPlayer) );
      
    }
    else
    {
      request->send(200, "text/plain", "0");
    }
  });

  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    Serial.println("le message est : " + message);
    gameStarted = message;
    Serial.println("gameStarted : " + gameStarted);

  });

  //requete pour envoyer gameStarted au client
  server.on("/gameStarted", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/plain", String(gameStarted));
  });

  server.begin();
}

void loop()
{

}