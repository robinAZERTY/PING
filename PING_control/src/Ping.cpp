#include "PING.hpp"

PING::PING()
{
    player1 = Player(DIR_PIN_1, INVERTED_DIR_PIN_1, STEP_PIN_1, END_STOP_PIN_1, SOLEOID_PIN_1, PHOTODIOD_PIN_1);
    player2 = Player(DIR_PIN_2, INVERTED_DIR_PIN_2, STEP_PIN_2, END_STOP_PIN_2, SOLEOID_PIN_2, PHOTODIOD_PIN_2);
    player3 = Player(DIR_PIN_3, INVERTED_DIR_PIN_3, STEP_PIN_3, END_STOP_PIN_3, SOLEOID_PIN_3, PHOTODIOD_PIN_3);
    player4 = Player(DIR_PIN_4, INVERTED_DIR_PIN_4, STEP_PIN_4, END_STOP_PIN_4, SOLEOID_PIN_4, PHOTODIOD_PIN_4);
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
    player1.play();
    player2.play();
    player3.play();
    player4.play();
}

bool PING::checkIsBallIn()
{
    bool condition = player1.isBallIn() || player2.isBallIn() || player3.isBallIn() || player4.isBallIn();
    return condition;
}

bool PING::isBallInStateChange()
{
    return player1.isBallInStateChange() || player2.isBallInStateChange() || player3.isBallInStateChange() || player4.isBallInStateChange();
}

uint8_t PING::getPlayerIdWichHasTheBallIn()
{
    if (player1.isBallIn())
        return 1;
    if (player2.isBallIn())
        return 2;
    if (player3.isBallIn())
        return 3;
    if (player4.isBallIn())
        return 4;
    return 0;
}
void PING::throwIn()
{
    player1.throwIn();
    player2.throwIn();
    player3.throwIn();
    player4.throwIn();
}

Player *PING::getPlayer(uint8_t id)
{
    switch (id)
    {
    case 1:
        return &player1;
    case 2:
        return &player2;
    case 3:
        return &player3;
    case 4:
        return &player4;
    }
    return NULL;
}

bool PING::waittingForThrowIn()
{
    return player1.isWaittingForThrowIn() || player2.isWaittingForThrowIn() || player3.isWaittingForThrowIn() || player4.isWaittingForThrowIn();
}

void PING::waitForThrowIn()
{
    player1.waitForThrowIn();
    player2.waitForThrowIn();
    player3.waitForThrowIn();
    player4.waitForThrowIn();
}

void PING::stop()
{
    player1.stop();
    player2.stop();
    player3.stop();
    player4.stop();
}

void PING::sonorInit()
{
    // wait for all calibration
    while (!player1.isReadyToPlay()||!player2.isReadyToPlay()||!player3.isReadyToPlay()||!player4.isReadyToPlay())
        delay(100);
    delay(1000);


    for (int i = 1; i < 10; i++)
    {
        Player *player = getPlayer(((i-1)%4 + 1));
        player->shoot();
        delay(500/i);
        player->release();
        delay(500/i);
    }
    delay(1000);
    for (int j = 0; j < 2; j++)
    {   
        for (int i = 0; i < 4; i++)
        {
            Player *player = getPlayer(i + 1);
            player->shoot();
        }
        delay(250);
        for (int i = 0; i < 4; i++)
        {
            Player *player = getPlayer(i + 1);
            player->release();
        }
        delay(250);
    }
    if (!player1.isReadyToPlay()||!player2.isReadyToPlay()||!player3.isReadyToPlay()||!player4.isReadyToPlay())
        sonorInit();
        
    _read_to_play = true;

    this->throwIn();
    
    while (true)
        delay(10000);
}

bool PING::isCalibrated()
{
    return player1.isCalibrated() && player2.isCalibrated() && player3.isCalibrated() && player4.isCalibrated();
}