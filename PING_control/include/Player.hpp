#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Linear_actuator.hpp"
#include "Solenoid.hpp"
#include "pin_configurations.hpp"

class Player
{
public:
    Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin);
    ~Player(){};

    void right(){linear_actuator.moveTo(MAX_POSITION);}
    void left(){linear_actuator.moveTo(0);}
    void stop(){linear_actuator.moveTo(linear_actuator.currentPosition());}

    void setPower(uint8_t p){solenoid.setPower(p);};
    void shoot(){solenoid.On();}
    void release(){solenoid.Off();}
    void play();

private:
    float _acceleration=5000.0, _speed=200.0;
    Solenoid solenoid;
    Linear_actuator linear_actuator;
};

#endif