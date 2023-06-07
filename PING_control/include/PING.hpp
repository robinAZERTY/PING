#ifndef PING_HPP
#define PING_HPP

#include "Player.hpp"

class PING
{
public:
    PING();
    ~PING(){};
    static Player player1, player2, player3, player4;
    static void init();
    static void play();
    static void throwIn();
};

#endif