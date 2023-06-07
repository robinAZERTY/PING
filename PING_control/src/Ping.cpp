#include "PING.hpp"

PING::PING()
{
    player1 = Player(DIR_PIN_1, STEP_PIN_1, END_STOP_PIN_1, SOLEOID_PIN_1, PHOTODIOD_PIN_1);
    player2 = Player(DIR_PIN_2, STEP_PIN_2, END_STOP_PIN_2, SOLEOID_PIN_2, PHOTODIOD_PIN_2);
    player3 = Player(DIR_PIN_3, STEP_PIN_3, END_STOP_PIN_3, SOLEOID_PIN_3, PHOTODIOD_PIN_3);
    player4 = Player(DIR_PIN_4, STEP_PIN_4, END_STOP_PIN_4, SOLEOID_PIN_4, PHOTODIOD_PIN_4);
}

void PING::init()
{
    player1.calibrate();
    player2.calibrate();
    player3.calibrate();
    player4.calibrate();
}


void PING::play()
{
    // check if a player take a shoot
    player1.isBallIn();
    player2.isBallIn();
    player3.isBallIn();
    player4.isBallIn();

    player1.play();
    player2.play();
    player3.play();
    player4.play();
}

void PING::throwIn()
{
    player1.throwIn();
    player2.throwIn();
    player3.throwIn();
    player4.throwIn();
}