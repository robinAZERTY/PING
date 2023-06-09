#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Linear_actuator.hpp"
#include "Solenoid.hpp"
#include "pin_configurations.hpp"

#define PHOTO_DIODE_TRESHOLD 3599

class Player
{
public:
    Player(){};
    Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin, int photodiod_pin );
    ~Player(){};

    void calibrate(){linear_actuator.calibrate();}

    void right(){linear_actuator.moveTo(MAX_POSITION);}
    void left(){linear_actuator.moveTo(0);}
    void stop(){linear_actuator.stop();}

    void setPower(uint8_t p){solenoid.setPower(p);};
    void shoot(){solenoid.On();}
    void release(){solenoid.Off();}
    void play();

    bool isAlive(){return _lives>0;}
    void resetLives(){_lives=_max_lives;}

    boolean isBallIn();
    void remove_a_Life(){_lives--;}
    void throwIn();//remise en jeu

private:
    float _acceleration=2000.0, _speed=200.0;
    Solenoid solenoid;
    Linear_actuator linear_actuator;
    uint8_t _photodiod_pin;
    boolean _waitting_for_throw_in = false;
    uint8_t _lives = 3, _max_lives = 3;
};

#endif