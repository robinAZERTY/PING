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
    void play();
    void throwIn();
};

#endif