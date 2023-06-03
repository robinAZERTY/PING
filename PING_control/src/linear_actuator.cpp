#include "linear_actuator.hpp"

linear_actuator::linear_actuator() : AccelStepper(AccelStepper::DRIVER)
{
    _end_stop_pin = -1;
}

linear_actuator::linear_actuator(int dir_pin, int step_pin, int end_stop_pin) : AccelStepper(AccelStepper::DRIVER, dir_pin, step_pin)
{
    _end_stop_pin = end_stop_pin;
    pinMode(_end_stop_pin, INPUT_PULLUP);
}


void  linear_actuator::stopEndStop()
{
    //force current speed to 0 and reset the position to 0
    setCurrentPosition(0);
    setSpeed(0);
    runSpeed();
}