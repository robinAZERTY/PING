#include "webConnection.hpp"

MyWebServer::MyWebServer()
{
    this->server = new AsyncWebServer(80);
    SSE = new AsyncEventSource("/SSE");
    SSE->onConnect([](AsyncEventSourceClient *client)
                   {
                       //on affiche d'ip du client
                          if (DEBUG)
                            Serial.println("Client connected to SSE("+client->client()->remoteIP().toString()+")");
                   });

    server->addHandler(SSE);
    this->connectedPlayer[0] = false;
    this->connectedPlayer[1] = false;
    this->connectedPlayer[2] = false;
    this->connectedPlayer[3] = false;

    this->playerLives[0] = this->maxLives;
    this->playerLives[1] = this->maxLives;
    this->playerLives[2] = this->maxLives;
    this->playerLives[3] = this->maxLives;
}

MyWebServer::~MyWebServer()
{
}

int MyWebServer::beginServer()
{

    // load all document
    if (!SPIFFS.begin())
        return -1;

    File root = SPIFFS.open("/");
    File file = root.openNextFile();

    while (file)
    {
        // register the path of the file in the list (adding a  '/' at the beginning)
        // pathList = (char **)realloc(pathList, (nbPath + 1) * sizeof(char *));
        // pathList[nbPath] = (char *)malloc((strlen(file.name()) + 2) * sizeof(char));
        // pathList[nbPath][0] = '/';
        // strcpy(pathList[nbPath] + 1, file.name());

        // nbPath++;
        // file.close();
        // file = root.openNextFile();
        file.close();
        file = root.openNextFile();
    }

    if (DEBUG)
    {
        Serial.println("Files in SPIFFS:");
        for (uint i = 0; i < nbPath; i++)
        {
            Serial.println(pathList[i]);
        }
    }

    WiFi.softAP(ssid, password);

    if (DEBUG)
        Serial.print("AP IP address: " + WiFi.softAPIP().toString());

    if (linkFiles() < 0)
        return -5;

    if (initPlayerChoice() < 0)
        return -2;

    if (initWaitingPage() < 0)
        return -3;

    if (initStartGameRequest() < 0)
        return -4;

    if (initGamePage() < 0)
        return -5;
    
    if (initGetLivesListRequest() < 0)
        return -6;

    server->begin();
    return 0;
}

// link extension to content type
const char *extMap[][2] =
    {
        {"html", "text/html"},
        {"css", "text/css"},
        {"js", "text/javascript"},
        {"png", "image/png"},
        {"gif", "image/gif"},
        {"jpg", "image/jpeg"},
        {"webp", "image/png"}};

const String MyWebServer::getContentType(const String path)
{
    String ext = path.substring(path.lastIndexOf('.') + 1);
    char *extChar = new char[ext.length() + 1];
    strcpy(extChar, ext.c_str());

    for (uint i = 0; i < sizeof(extMap) / sizeof(extMap[0]); i++)
    {
        if (strcmp(extChar, extMap[i][0]) == 0)
            return extMap[i][1];
    }

    return ext;
}

int MyWebServer::linkFile(const char *url, const char *path, const char *contentType)
{

    String strPath = String(path);
    String strContentType = String(contentType);
    if(DEBUG)
        Serial.println("Linking file: '" + strPath + "' with content type: '" + strContentType+"'"+ " and url: '"+String(url)+"'");

    server->on(url, HTTP_GET, [strPath, strContentType, url](AsyncWebServerRequest *request)
               {
                    if (DEBUG)
                        Serial.println("Linked file: '" + strPath + "' with content type: '" + String(strContentType)+"'"+ " and url: '"+String(url)+"'");
                    
                    request->send(SPIFFS, String(strPath), String(strContentType)); });

    return 0;
}

int MyWebServer::linkFiles()
{
    // for (uint i = 0; i < nbPath; i++)
    // {
    //     linkFile(pathList[i], pathList[i], getContentType(pathList[i]).c_str());
    // }
    // return 0;

    server->on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request)
               {request->send(SPIFFS, "/index.html", "text/html"); });

    server->on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/index.js", "text/javascript"); });
    
    server->on("/playerChoice.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/playerChoice.html", "text/html"); });

    server->on("/game_page_infini.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/game_page_infini.html", "text/html"); });


    server->on("/playerChoice.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/playerChoice.js", "text/javascript"); });
    
    server->on("/waiting_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/waiting_page.html", "text/html"); });

    server->on("/waiting_page.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/waiting_page.js", "text/javascript"); });
    
    server->on("/start.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/start.html", "text/html"); });

    server->on("/start.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/start.js", "text/javascript"); });

    server->on("/story.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/story.html", "text/html"); });

    server->on("/story.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/story.js", "text/javascript"); });

    server->on("/rules.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/rules.html", "text/html"); });

    server->on("/rules.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/rules.js", "text/javascript"); });

    server->on("/game_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/game_page.html", "text/html"); });

    server->on("/game_page.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/game_page.js", "text/javascript"); });
    
    server->on("/score.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/score.html", "text/html"); });

    server->on("/score.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/score.js", "text/javascript"); });

    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/style.css", "text/css"); });

    server->on("/SSE.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/SSE.js", "text/javascript"); });

               
    //--------------------------------------------Images--------------------------------------------------------

    server->on("/robin.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/robin.png", "image/png"); });

    server->on("/baptiste1.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/baptiste1.png", "image/png"); });

    server->on("/baptiste2.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/baptiste2.png", "image/png"); });

    server->on("/LOGO.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/LOGO.png", "image/png"); });

    server->on("/simon.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/simon.png", "image/png"); });

    server->on("/franck.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/franck.png", "image/png"); });

    server->on("/thomas.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/thomas.png", "image/png"); });

    server->on("/coeur.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/coeur.png", "image/png"); });
               
    server->on("/trophee.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/trophee.png", "image/png"); });

    server->on("/medaille-dargent.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/medaille-dargent.png", "image/png"); });

    server->on("/medaille-de-bronze.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/medaille-de-bronze.png", "image/png"); });

    server->on("/merde.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/merde.png", "image/png"); });

    server->on("/setting.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/setting.png", "image/png"); });

    server->on("/wifi.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/wifi.png", "image/png"); });
   
    server->on("/infini.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/infini.png", "image/png"); });

    return 0;
}

void MyWebServer::sendToSerial(HardwareSerial &serial)
{
    if (toSendToSerial == "")
        return;

    if (DEBUG)
        Serial.println("Sending to serial: ");

    serial.print(toSendToSerial);
    toSendToSerial = "";
}

int MyWebServer::dealWithMsg(String str) // on traite la le message reçu sur le port série
{
    if(DEBUG)
        Serial.println("Received from serial: "+str);

    // str est dans le format requete http : /goalTaken?playerId=1
    //  check if the request is in the list
    String url = str.substring(0, str.indexOf('?'));
    if (url != "/goalTaken")
        return -1;

        // de la forme 
//goalTaken?playerId=2
    
    // on verifie la présence de l'argument playerId
    String arg = str.substring(str.indexOf('?') + 1, str.indexOf('='));
    if (arg != "playerId")
        return -1;

    // get the parameters
    int playerId = str.substring(str.indexOf('=') + 1,str.indexOf("\n")).toInt();

    // on verifie que le playerId est valide
    if (playerId < 0 || playerId > 3)
        return -1;

    if(DEBUG)
        Serial.println("Player "+String(playerId)+" has taken a goal");

    return playerId;
}

void MyWebServer::receiveFromSerial(HardwareSerial &serial)
{

    if (serial.available() <= 0)
        return;

    if (DEBUG)
        Serial.println("Receiving from serial: ");

    // read until the end of the line
    receivedFromSerial += serial.readStringUntil('\n') + '\n';
    // cherche si le message est valide
    int id = dealWithMsg(receivedFromSerial);
    if (id == -1)
    {
        receivedFromSerial = "";
        return;
    }
    // si oui, on la traite
    if(gameMode =="classic")
        {
            this->playerLives[id]--;
        }
    else if(gameMode =="infinite")
        {
            // do nothing
        }
    else
    {
        throw "Game mode not recognized";
    } 
    
    if(DEBUG)
        Serial.println("Player "+String(id)+" has "+String(this->playerLives[id])+" lives left");
    
    String toSend = "/goalTaken?playerId=";//ex 
//goalTaken?playerId=3

    toSend+=String(id);
    SSE->send(toSend.c_str(),NULL,millis(),100);

    // on regarde si le joueur est mort
    if (this->playerLives[id] == 0)
    {
        SSE->send("/gameEnded",NULL,millis(),100);
    }
    else 
    {
        if (gameMode=="classic")
        { 
        //on envoit le nombre de vie restante
        String toSend = "/remainingLives?playerId=";
        toSend+=String(id);
        toSend+="&lives=";
        toSend+=String(this->playerLives[id]);
        SSE->send(toSend.c_str(),NULL,millis(),100);
        }
    }
    if (DEBUG)
        Serial.println("Request found: " + receivedFromSerial);
    
    receivedFromSerial = "";
}