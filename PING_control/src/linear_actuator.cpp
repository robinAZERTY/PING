#include "Linear_actuator.hpp"



Linear_actuator::Linear_actuator(int dir_pin, int step_pin, int end_stop_pin) {
  stepper = AccelStepper(AccelStepper::DRIVER, dir_pin, step_pin);
  _end_stop_pin = end_stop_pin;
  _calibrated = true;//don't calibrate at the beginning
  _calibrating = false;
  if (_end_stop_pin > 0)
    pinMode(_end_stop_pin, INPUT_PULLUP);
}

void Linear_actuator::calibrate() {

  _calibrated = false;
  _calibrating = true;
  moveTo(CALIBRATION_MAX_TRAVEL);
}

void Linear_actuator::run() {

  stepper.run();  //move the stepper;

  if (!_calibrating)
    return;

  bool condition = (_end_stop_pin > 0) ? !digitalRead(_end_stop_pin)|currentPosition() > CALIBRATION_MAX_TRAVEL : (currentPosition() > CALIBRATION_MAX_TRAVEL);
 
  if (!condition) 
    return;

  stepper.setSpeed(0);
  stepper.runSpeed();
  setCurrentPosition(MAX_POSITION);  // parceque l'endstop est au bout de la course
  moveTo(MAX_POSITION/2);
  _calibrating = false;
  _calibrated = true;
}

void Linear_actuator::moveTo(float absolute_mm) {

  if (absolute_mm > MAX_POSITION)
    absolute_mm = MAX_POSITION;
  else if (absolute_mm < 0)
    absolute_mm = 0;
  stepper.moveTo((long)(absolute_mm * STEP_PER_MM));
}

void Linear_actuator::resumeCalibration() {
  if (_calibrated)
    return;
  _calibrating = false;
  calibrate();
}