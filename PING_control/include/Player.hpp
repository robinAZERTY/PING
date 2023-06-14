#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Linear_actuator.hpp"
#include "Solenoid.hpp"
#include "pin_configurations.hpp"

#define PHOTO_DIODE_TRESHOLD 3599
#define SECURE_DISTANCE 20
#define BALL_SECURE_TIME 1000

class Player
{
public:
    Player(){};
    Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin, int photodiod_pin );
    ~Player(){};

    void calibrate(){linear_actuator.calibrate();}
    
    void right();
    void left();
    void stop();

    void waitForThrowIn(){_waitting_for_throw_in = true;};

    void setPower(uint8_t p){solenoid.setPower(p);};
    void shoot();
    void release();
    void play();

    boolean isBallIn();
    void throwIn();//remise en jeu

    boolean isWaittingForThrowIn(){_previous_ball_in_state=_waitting_for_throw_in;return _waitting_for_throw_in;}
    boolean isBallInStateChange(){return _previous_ball_in_state!=_waitting_for_throw_in;}
    boolean isCalibrated(){return linear_actuator.isCalibrated();}
    boolean isMoving(){return linear_actuator.distanceToGo()!=0;}
    boolean isReadyToPlay(){return _ready_to_play;}
private:
    float _acceleration=2000.0, _speed=200.0;
    Solenoid solenoid;
    Linear_actuator linear_actuator;
    uint8_t _photodiod_pin;
    boolean _waitting_for_throw_in = false, _previous_ball_in_state = false, _ready_to_play = false;
    unsigned long _time_of_last_ball_in = 0;
};

#endif