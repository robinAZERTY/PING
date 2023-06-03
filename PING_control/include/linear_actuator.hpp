#ifndef LINEAR_ACTUATOR_HPP
#define LINEAR_ACTUATOR_HPP

#include <Arduino.h>
#include <AccelStepper.h>

/* 
la classe linear_actuator hérite de la classe AccelStepper avec quelques fonctionnalités en plus:
- routine d'interruption sur le pin du fin de course
*/

class linear_actuator : public AccelStepper
{
    public :
        linear_actuator();
        linear_actuator(int dir_pin, int step_pin, int end_stop_pin);
    
    private :
        void stopEndStop();
        int _end_stop_pin;
};

#endif