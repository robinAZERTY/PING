#include "Player.hpp"

Player::Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin, int photodiod_pin)
{
    solenoid = Solenoid(solenoid_pin);
    solenoid.setPower(255);
    solenoid.Off();
    solenoid.run(); // set off to begin
    linear_actuator = Linear_actuator(dir_pin, step_pin, end_stop_pin);
    linear_actuator.setMaxSpeed(_speed);
    linear_actuator.setAcceleration(_acceleration);
    _photodiod_pin = photodiod_pin;
    pinMode(_photodiod_pin, INPUT);
}

void Player::right()
{
    if (_waitting_for_throw_in)
        return;
    linear_actuator.moveTo(MAX_POSITION);
}

void Player::left()
{
    if (_waitting_for_throw_in)
        return;
    linear_actuator.moveTo(0);
}

void Player::stop()
{
    linear_actuator.stop();
}

void Player::shoot()
{
    if (_waitting_for_throw_in)
        return;
    solenoid.On();
}

void Player::release()
{
    solenoid.Off();
}

void Player::play()
{
    linear_actuator.run();
    solenoid.run();

    if (isCalibrated()&&!_ready_to_play&&linear_actuator.currentPosition()==MAX_POSITION/2)
        _ready_to_play = true;
}

boolean Player::isBallIn()
{
    if (analogRead(_photodiod_pin) < PHOTO_DIODE_TRESHOLD) // if the ball is not in the player
        {
            if(millis()-_time_of_last_ball_in>BALL_SECURE_TIME)
                {
                    if (!isCalibrated())
                    {
                        linear_actuator.resumeCalibration();
                    }
                    if(isCalibrated()&&!_ready_to_play&&linear_actuator.currentPosition()!=MAX_POSITION/2)
                        linear_actuator.moveTo(MAX_POSITION/2);
                    
                    _waitting_for_throw_in = false;
                    return false;
                }
            return true;
        }

    _time_of_last_ball_in = millis();

    // if the ball is in the player
    _waitting_for_throw_in = true;

    // stop the calibration if it is running
    linear_actuator.breakCalibration();

    // make sure the solenoid is off
    release();
    stop();

    // make sure the player is in a safe position
    if (linear_actuator.currentPosition() < SECURE_DISTANCE)
        linear_actuator.moveTo(SECURE_DISTANCE);
    else if (linear_actuator.currentPosition() > MAX_POSITION - SECURE_DISTANCE)
        linear_actuator.moveTo(MAX_POSITION - SECURE_DISTANCE);

    return true;
}

void Player::throwIn()
{
    // is calibrated ?
    if (!linear_actuator.isCalibrated())
        calibrate();
    else
    {
    linear_actuator.moveTo(MAX_POSITION / 2);
    _waitting_for_throw_in = false;
    }
}