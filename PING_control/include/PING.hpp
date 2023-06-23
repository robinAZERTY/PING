#ifndef PING_HPP
#define PING_HPP

#include "Player.hpp"

class PING
{
public:
    PING();
    ~PING(){};
    Player player1,player2, player3, player4;
    void init();
    void sonorInit();
    void play();
    void waitForThrowIn();
    void stop();
    void throwIn();
    bool checkIsBallIn();
    int isBallInStateChange();
    bool waittingForThrowIn();
    bool isCalibrated();
    bool isReadToPlay(){return _read_to_play;}
    Player *getPlayer(uint8_t id);
    uint8_t getPlayerIdWichHasTheBallIn();

private:
    boolean _read_to_play = false;
};

#endif