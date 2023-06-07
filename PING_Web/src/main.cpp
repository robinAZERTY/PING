#include <Arduino.h>
#include <ESPAsyncWebServer.h>
//Udp Library
//#include <EspAsyncUDP.h>
#include <SPIFFS.h>

const char *ssid = "esp32";
const char *password = "123456789";


const int right = 2;
const int left = 3;
const int push = 4;
// const int motor1 = ;
// const int motor2 = ;
// const int motor3 = ;
// const int motor4 = ;

AsyncWebServer server(80);
//Async Udp Server
//AsyncUDP udp;

// Request Handle for broadcasting message
// void handleRequest(AsyncWebServerRequest *request) {
//   String message = "Ceci est la requete Update";
//   udp.broadcastTo(message.c_str(), 1234); //Broadcast the message to all devices on the network
//   request->send(200, "text/plain", "Update sent");
// }

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
    Serial.println("On avance à droite");
    request->send(200);
  });

  server.on("/rightUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("STOP a droite");
    request->send(200);
  });


  server.on("/leftDown", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("On avance à gauche");
    request->send(200);
  });

    server.on("/leftUp", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("STOP a gauche");
    request->send(200);
  });

  server.on("/push", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("push");
    request->send(200);
  });

  // Broadcast de la page
  //server.on("/start", HTTP_GET, handleRequest);


  server.begin();
  Serial.println("Serveur actif!");
}

void loop()
{

}