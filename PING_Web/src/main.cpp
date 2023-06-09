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

  server.on("/scores.html", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/scores.html", "text/html");
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
   /* switch (recievedPlayerId)
    {
    case 1:
      //Serial.println("Joueur 1 avance à droite");
      break;
    case 2:
      //Serial.println("Joueur 2 avance à droite");
      break;
    case 3:
      //Serial.println("Joueur 3 avance à droite");
      break;
    case 4:
      //Serial.println("Joueur 4 avance à droite");
      break;
    default:
      break;
    }*/
    request->send(200);
  });

  server.on("/rightUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    //on récupère les paramètres de la requête
    String message = request->getParam(0)->value();
    //on convertit le message en int
    int recievedPlayerId = message.toInt();
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche
    /*switch (recievedPlayerId)
    {
    case 1:
      //Serial.println("Joueur 1 STOP à droite");
      break;
    case 2:
      //Serial.println("Joueur 2 STOP à droite");
      break;
    case 3:
      //Serial.println("Joueur 3 STOP à droite");
      break;
    case 4:
      //Serial.println("Joueur 4 STOP à droite");
      break;
    default:
      break;
    }*/
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
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche
   /* switch (recievedPlayerId)
    {
    case 1:
      //Serial.println("Joueur 1 avance à gauche");
      break;
    case 2:
      //Serial.println("Joueur 2 avance à gauche");
      break;
    case 3:
      //Serial.println("Joueur 3 avance à gauche");
      break;
    case 4:
      //Serial.println("Joueur 4 avance à gauche");
      break;
    default:
      break;
    }
    */
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
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche
    

    /*switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 STOP à gauche");
      break;
    case 2:
      Serial.println("Joueur 2 STOP à gauche");
      break;
    case 3:
      Serial.println("Joueur 3 STOP à gauche");
      break;
    case 4:
      Serial.println("Joueur 4 STOP à gauche");
      break;
    default:
      break;
    }
    */
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
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche
    /*switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 Push");
      break;
    case 2:
      Serial.println("Joueur 2 Push");
      break;
    case 3:
      Serial.println("Joueur 3 Push");
      break;
    case 4:
      Serial.println("Joueur 4 Push");
      break;
    default:
      break;
    }
    */
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
    //en fonction du joueur on effectue une action différente avec un switch
    //si id=1 on print le joueur id avance à gauche
    /*switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 STOP Push");
      break;
    case 2:
      Serial.println("Joueur 2 STOP Push");
      break;
    case 3:
      Serial.println("Joueur 3 STOP Push");
      break;
    case 4:
      Serial.println("Joueur 4 STOP Push");
      break;
    default:
      break;
    }
    */
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

  server.begin();
}

void loop()
{

}