#ifndef LINEAR_ACTUATOR_HPP
#define LINEAR_ACTUATOR_HPP

#include <Arduino.h>
#include <AccelStepper.h>

/*
la classe Linear_actuator hérite de la classe AccelStepper avec quelques fonctionnalités en plus:
- arret du moteur quand l'endstop est atteint
- conversion des pas en mm
*/

#define MICROSTEP 8             // microspas par pas (dépend de la configuration du driver)
#define BELT_PITCH 2             // mm par dent de la courroie (dépend de la courroie)
#define POULLEY_TEETH 25         // dents par poullie (dépend de la poullie)
#define STEPS_PER_REVOLUTION 200 // nombre de pas entier par tour (dépend du moteur)
#define MAX_POSITION 275         // mm (dépend de la longueur de la course)


class Linear_actuator
{
public:
    Linear_actuator(){};
    Linear_actuator(int dir_pin, int step_pin, int end_stop_pin);
    ~Linear_actuator(){};
    void calibrate(); // when we want to check for a new falling edge
    void moveTo(float absolute_mm);
    void run();
    void move(float relative_mm){ stepper.move((long)(relative_mm * STEP_PER_MM));}
    void setSpeed(float speed_mm_per_sec) { stepper.setSpeed(speed_mm_per_sec * STEP_PER_MM);}
    void setMaxSpeed(float speed_mm_per_sec) { stepper.setMaxSpeed(speed_mm_per_sec * STEP_PER_MM);}
    void setAcceleration(float acceleration_mm_per_sec2) { stepper.setAcceleration(acceleration_mm_per_sec2 * STEP_PER_MM);}
    float acceleration() { return stepper.acceleration() / STEP_PER_MM;}
    float speed() { return stepper.speed() / STEP_PER_MM;}
    float maxSpeed() { return stepper.maxSpeed() / STEP_PER_MM;}
    float distanceToGo() { return stepper.distanceToGo() / STEP_PER_MM;}
    float targetPosition() { return stepper.targetPosition() / STEP_PER_MM;}
    float currentPosition() { return stepper.currentPosition() / STEP_PER_MM;}
    void setCurrentPosition(float position_mm) { stepper.setCurrentPosition(position_mm * STEP_PER_MM);}
    void runToNewPosition(float position_mm) { stepper.runToNewPosition(position_mm * STEP_PER_MM);}
    void stop(){ stepper.stop();}


    
private:
    AccelStepper stepper;
    static constexpr float STEP_PER_MM = (float)STEPS_PER_REVOLUTION * MICROSTEP / BELT_PITCH / POULLEY_TEETH,CALIBRATION_SPEED = 100.0;
    int _end_stop_pin;
    bool _calibrated;
};

#endif