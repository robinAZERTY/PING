#include "Linear_actuator.hpp"



Linear_actuator::Linear_actuator(int dir_pin, int step_pin, int end_stop_pin)
{
    stepper = AccelStepper(AccelStepper::DRIVER, dir_pin, step_pin);
    _end_stop_pin = end_stop_pin;
    _check_for_falling_edge = true;
    pinMode(_end_stop_pin, INPUT_PULLUP);

}



void Linear_actuator::run()
{
    stepper.run();
    if(!_check_for_falling_edge)
      return;
    if(stepper.speed()<=0)
      return;

    //check if the endstop is reached
    //bool end_stop_state = (*portInputRegister(digitalPinToPort(_end_stop_pin)) & _pin_mask);
    bool end_stop_state = digitalRead(_end_stop_pin);
    if(!end_stop_state ) 
    {
        //_check_for_falling_edge = false;
        stepper.setSpeed(0);
        stepper.runSpeed();
        setCurrentPosition(MAX_POSITION);// parceque l'endstop est au bout de la course
    }
}

void Linear_actuator::moveTo(float absolute_mm)
{
    if(absolute_mm > MAX_POSITION)
        absolute_mm = MAX_POSITION;
    else if(absolute_mm < 0)
        absolute_mm = 0;
    stepper.moveTo((long)(absolute_mm * STEP_PER_MM));
}