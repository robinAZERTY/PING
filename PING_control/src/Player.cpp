#include "Player.hpp"

Player::Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin, int photodiod_pin)
{
    solenoid = Solenoid(solenoid_pin);
    solenoid.setPower(255);
    solenoid.Off();
    solenoid.run();//set off to begin
    linear_actuator = Linear_actuator(dir_pin, step_pin, end_stop_pin);
    linear_actuator.setMaxSpeed(_speed);
    linear_actuator.setAcceleration(_acceleration);
    _photodiod_pin = photodiod_pin;
    pinMode(_photodiod_pin, INPUT);
}

void Player::play()
{
    if (_waitting_for_throw_in)
        return;

    linear_actuator.run();
    solenoid.run();
}

boolean Player::isBallIn()
{
    if (analogRead(_photodiod_pin)<PHOTO_DIODE_TRESHOLD)// if the ball is not in the player
        return false;

    _waitting_for_throw_in = true;
    
    //make shure the solenoid is off
    solenoid.Off();
    return true;
}

void Player::throwIn()
{
    linear_actuator.moveTo(MAX_POSITION/2);
    _waitting_for_throw_in = false;
}