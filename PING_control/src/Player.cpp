#include "Player.hpp"

Player::Player(int dir_pin, int step_pin, int end_stop_pin, int solenoid_pin)
{
    solenoid = Solenoid(solenoid_pin);
    solenoid.setPower(255);
    solenoid.Off();
    solenoid.run();//set off to begin
    linear_actuator = Linear_actuator(dir_pin, step_pin, end_stop_pin);
    linear_actuator.setMaxSpeed(_speed);
    linear_actuator.setAcceleration(_acceleration);
}

void Player::play()
{
    linear_actuator.run();
    solenoid.run();
}