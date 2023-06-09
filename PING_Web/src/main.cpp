#include <Arduino.h>
#include <ESPAsyncWebServer.h>
//Udp Library
//#include <EspAsyncUDP.h>
#include <SPIFFS.h>

const char *ssid = "esp32";
const char *password = "123456789";


const int right = 4;
const int left = 21;
const int push = 18;
// const int motor1 = ;
// const int motor2 = ;
// const int motor3 = ;
// const int motor4 = ;

AsyncWebServer server(80);

bool choosenPlayer[4] = {0,0,0,0};

void setup()
{
  
  //----------------------------------------------------Serial
  Serial.begin(115200);
  Serial.println("\n");

  //----------------------------------------------------GPIO
  pinMode(right, OUTPUT);
  digitalWrite(right, LOW);
  pinMode(left, OUTPUT);
  digitalWrite(left, LOW);
  pinMode(push, OUTPUT);
  digitalWrite(push, LOW);

  //----------------------------------------------------SPIFFS
  if(!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  //----------------------------------------------------WIFI
  Serial.println("Creation du point d'acces...");
	WiFi.softAP(ssid, password);
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.softAPIP());

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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 avance à droite");
      digitalWrite(right, HIGH);
      break;
    case 2:
      Serial.println("Joueur 2 avance à droite");
      break;
    case 3:
      Serial.println("Joueur 3 avance à droite");
      break;
    case 4:
      Serial.println("Joueur 4 avance à droite");
      break;
    default:
      break;
    }
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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 STOP à droite");
      digitalWrite(right, LOW);
      break;
    case 2:
      Serial.println("Joueur 2 STOP à droite");
      break;
    case 3:
      Serial.println("Joueur 3 STOP à droite");
      break;
    case 4:
      Serial.println("Joueur 4 STOP à droite");
      break;
    default:
      break;
    }
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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 avance à gauche");
      digitalWrite(left, HIGH);
      break;
    case 2:
      Serial.println("Joueur 2 avance à gauche");
      break;
    case 3:
      Serial.println("Joueur 3 avance à gauche");
      break;
    case 4:
      Serial.println("Joueur 4 avance à gauche");
      break;
    default:
      break;
    }
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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 STOP à gauche");
      digitalWrite(left, LOW);
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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 Push");
      digitalWrite(push, HIGH);
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
    switch (recievedPlayerId)
    {
    case 1:
      Serial.println("Joueur 1 STOP Push");
      digitalWrite(push, LOW);
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
  Serial.println("Serveur actif!");
}

void loop()
{

}