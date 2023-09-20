#include "webConnection.hpp"

MyWebServer::MyWebServer()
{
    this->server = new AsyncWebServer(80);
    SSE = new AsyncEventSource("/SSE");
    SSE->onConnect([](AsyncEventSourceClient *client)
                   {
                       //on affiche d'ip du client
                          if (DEBUG)
                            Serial.println("Client connected to SSE("+client->client()->remoteIP().toString()+")"); });

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
    if (!FLASH_TYPE.begin())
        return -1;

    File root = FLASH_TYPE.open("/");
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
        Serial.println("Files in FLASH_TYPE:");
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

    if (initGetRedirectingPlayerRequest() < 0)
        return -7;

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
    if (DEBUG)
        Serial.println("Linking file: '" + strPath + "' with content type: '" + strContentType + "'" + " and url: '" + String(url) + "'");

    server->on(url, HTTP_GET, [strPath, strContentType, url](AsyncWebServerRequest *request)
               {
                    if (DEBUG)
                        Serial.println("Linked file: '" + strPath + "' with content type: '" + String(strContentType)+"'"+ " and url: '"+String(url)+"'");
                    
                    request->send(FLASH_TYPE, String(strPath), String(strContentType)); });

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
               { request->send(FLASH_TYPE, "/index.html", "text/html"); });

    server->on("/index.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/index.js", "text/javascript"); });

    server->on("/playerChoice.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/playerChoice.html", "text/html"); });

    server->on("/game_page_infini.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/game_page_infini.html", "text/html"); });

    server->on("/playerChoice.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/playerChoice.js", "text/javascript"); });

    server->on("/waiting_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/waiting_page.html", "text/html"); });

    server->on("/waiting_page.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/waiting_page.js", "text/javascript"); });

    server->on("/start.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/start.html", "text/html"); });

    server->on("/start.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/start.js", "text/javascript"); });

    server->on("/story.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/story.html", "text/html"); });

    server->on("/story.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/story.js", "text/javascript"); });

    server->on("/rules.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/rules.html", "text/html"); });

    server->on("/rules.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/rules.js", "text/javascript"); });

    server->on("/game_page.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/game_page.html", "text/html"); });

    server->on("/game_page.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/game_page.js", "text/javascript"); });

    server->on("/score.html", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/score.html", "text/html"); });

    server->on("/score.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/score.js", "text/javascript"); });

    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/style.css", "text/css"); });

    server->on("/SSE.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/SSE.js", "text/javascript"); });

    //--------------------------------------------Images--------------------------------------------------------

    server->on("/robin.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/robin.png", "image/png"); });

    server->on("/baptiste1.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/baptiste1.png", "image/png"); });

    server->on("/baptiste2.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/baptiste2.png", "image/png"); });

    server->on("/LOGO.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/LOGO.png", "image/png"); });

    server->on("/simon.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/simon.png", "image/png"); });

    server->on("/franck.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/franck.png", "image/png"); });

    server->on("/thomas.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/thomas.png", "image/png"); });

    server->on("/coeur.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/coeur.png", "image/png"); });

    server->on("/trophee.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/trophee.png", "image/png"); });

    server->on("/medaille-dargent.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/medaille-dargent.png", "image/png"); });

    server->on("/medaille-de-bronze.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/medaille-de-bronze.png", "image/png"); });

    server->on("/merde.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/merde.png", "image/png"); });

    server->on("/setting.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/setting.png", "image/png"); });

    server->on("/wifi.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/wifi.png", "image/png"); });

    server->on("/infini.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/infini.png", "image/png"); });

    server->on("/logo_bleu.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/logo_bleu.png", "image/png"); });

    server->on("/logo_rouge.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/logo_rouge.png", "image/png"); });

    server->on("/logo_vert.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/logo_vert.png", "image/png"); });

    server->on("/logo_jaune.png", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(FLASH_TYPE, "/logo_jaune.png", "image/png"); });

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
    if (DEBUG)
        Serial.println("Received from serial: " + str);

    // str est dans le format requete http : /goalTaken?playerId=1
    //  check if the request is in the list
    String url = str.substring(0, str.indexOf('?'));
    if (url != "/goalTaken")
        return -1;

    // de la forme
    // goalTaken?playerId=2

    // on verifie la présence de l'argument playerId
    String arg = str.substring(str.indexOf('?') + 1, str.indexOf('='));
    if (arg != "playerId")
        return -1;

    // get the parameters
    int playerId = str.substring(str.indexOf('=') + 1, str.indexOf("\n")).toInt();

    // on verifie que le playerId est valide
    if (playerId < 0 || playerId > 3)
        return -1;

    if (DEBUG)
        Serial.println("Player " + String(playerId) + " has taken a goal");

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
    if (gameMode == "classic")
    {
        this->playerLives[id]--;
    }
    else if (gameMode == "infinite")
    {
        // do nothing
    }
    else
    {
        throw "Game mode not recognized";
    }

    if (DEBUG)
        Serial.println("Player " + String(id) + " has " + String(this->playerLives[id]) + " lives left");

    String toSend = "/goalTaken?playerId="; // ex
    // goalTaken?playerId=3

    toSend += String(id);
    SSE->send(toSend.c_str(), NULL, millis(), 100);

    // on regarde si le joueur est mort
    if (this->playerLives[id] == 0)
    {
        SSE->send("/gameEnded", NULL, millis(), 100);
    }
    else
    {
        if (gameMode == "classic")
        {
            // on envoit le nombre de vie restante
            String toSend = "/remainingLives?playerId=";
            toSend += String(id);
            toSend += "&lives=";
            toSend += String(this->playerLives[id]);
            SSE->send(toSend.c_str(), NULL, millis(), 100);
        }
    }
    if (DEBUG)
        Serial.println("Request found: " + receivedFromSerial);

    receivedFromSerial = "";
}

int MyWebServer::initGetRedirectingPlayerRequest()
{
    server->on("/redirectingAvailability", HTTP_GET, [this](AsyncWebServerRequest *request)
               {
        // redirectingAvailability?type=GET or redirectingAvailability?type=FREE
        if (request->hasParam("type"))
        {  
            AsyncWebParameter *p = request->getParam("type");
            if (p->value() == "GET")
            {
                if (redirectingPlayer < MAX_SIMULTANEOUS_REDIRECTION)
                {
                    if (DEBUG) Serial.println("new redirecting");
                    redirectingPlayer++;
                    request->send(200, "text/plain", "available");
                }
                else
                {
                    if (DEBUG) Serial.println("busy");
                    request->send(200, "text/plain", "busy");
                }
            }
            else if (p->value() == "FREE")
            {
                if (DEBUG) Serial.println("free redirectingPlayer");
                redirectingPlayer--;
                redirectingPlayer = (redirectingPlayer < 0) ? 0 : redirectingPlayer;
                request->send(200, "text/plain", "FREE");
            }
        }
        else
        {
            request->send(200, "text/plain", "error");
        } });

    return 0;
}