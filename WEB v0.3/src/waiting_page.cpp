#include "webConnection.hpp"

#define DEBUG true

int MyWebServer::initWaitingPage()
{
    waitingPage_SSE();
    return 0;
}
void MyWebServer::waitingPage_SSE()
{
    gameStartedSSE = new AsyncEventSource("/getGameStarted_SSE");
    // Définir la fonction de gestion de l'événement "connect"
    gameStartedSSE->onConnect([](AsyncEventSourceClient *client)
                              {
                                  if (DEBUG)
                                      Serial.println("Client connected to GameStarted SSE");
                                  // Code à exécuter lorsque le client se connecte
                              });
    // Ajouter l'événement au serveur
    server->addHandler(gameStartedSSE);
}