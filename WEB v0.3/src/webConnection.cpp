#include "webConnection.hpp"

#define DEBUG false

MyWebServer::MyWebServer()
{
    this->server = new AsyncWebServer(80);
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
        pathList = (char **)realloc(pathList, (nbPath + 1) * sizeof(char *));
        pathList[nbPath] = (char *)malloc((strlen(file.name()) + 1) * sizeof(char));
        strcpy(pathList[nbPath], file.name());

        nbPath++;
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
    server->on(url, HTTP_GET, [strPath, strContentType, url](AsyncWebServerRequest *request)
               {
                    if (DEBUG)
                        Serial.println("Linked file: '" + strPath + "' with content type: '" + String(strContentType)+"'"+ " and url: '"+String(url)+"'");
                    
                    request->send(SPIFFS, String(strPath), String(strContentType)); });

    return 0;
}

int MyWebServer::linkFiles()
{
    for (uint i = 0; i < nbPath; i++)
    {
        linkFile(pathList[i], pathList[i], getContentType(pathList[i]).c_str());
    }
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
    this->playerLives[id]--;
    if(DEBUG)
        Serial.println("Player "+String(id)+" has "+String(this->playerLives[id])+" lives left");
    getGoalTaken_SSE->send(String(id).c_str());

    if (id == 0)
        getLives_SSE_0->send(String(this->playerLives[0]).c_str());
    else if (id == 1)
        getLives_SSE_1->send(String(this->playerLives[1]).c_str());
    else if (id == 2)
        getLives_SSE_2->send(String(this->playerLives[2]).c_str());
    else if (id == 3)
        getLives_SSE_3->send(String(this->playerLives[3]).c_str());
    
    

    // on regarde si le joueur est mort
    if (this->playerLives[id] == 0)
    {
        getEndGame_SSE->send("gameEnded");
    }
    if (DEBUG)
        Serial.println("Request found: " + receivedFromSerial);
    
    receivedFromSerial = "";
}