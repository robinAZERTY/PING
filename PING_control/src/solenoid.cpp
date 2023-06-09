#include "Solenoid.hpp"
#include "Arduino.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Solenoid::Solenoid(int pwm_pin) {
  // parametres par défaut du modèle thermique
  Tp = 5.0;  // durée max à pleine puissance
  r = 0.2;   // en moyenne 20% du temps à pleine puissance est toléré

  compute_A_B();

  // initialisation
  _power = 0;
  
  _pin = pwm_pin;
  pinMode(_pin, OUTPUT);
  analogWrite(_pin, 0);
  _y_off = 0.0;
  _y_on=0;
  _t_off=millis();
  _t_on=_t_off;
  }

Solenoid::~Solenoid() {
}

void Solenoid::setPower(uint8_t power) {
  _power = power;
  compute_A_B();
}

void Solenoid::setMaxDuration(float d_max)
{
  Tp=d_max;
  compute_A_B();
}

void Solenoid::compute_A_B()
{
  // calculs des coefficients
  B = -1.0 / (Tp / r - Tp);  // coefficient de la dissipation thermique
  A = 1 / Tp - B;            // coefficient de la montée en température
}
void Solenoid::setAvrPower(float avr_power)
{
  _avr_power=avr_power;
}
void Solenoid::On() {

  if (_state == _power)
    return;

  _t_on = millis();
  _y_on = _y_off + B * (_t_on - _t_off) / 1000.0;
  _y_on = max(_y_on, 0.0);
  _t_L = 1000.0 * (1.0 - _y_on) / (_power / 255.0 * A + B) + _t_on;
  _state = _power;
}

void Solenoid::Off() {

  if (_state == 0)
    return;

  _t_off = millis();
  _y_off = _y_on + (_power / 255.0 * A + B) * (_t_off - _t_on) / 1000.0;
  _y_off = min(_y_off, 1.0);

  _state = 0;
}

void Solenoid::run() {

  if (millis() >= _t_L)
    Off();

  if (_state != _prev_state) {
    _prev_state = _state;
    analogWrite(_pin, _state);
  }
}

float Solenoid::getWarmup()
{
  if(_state==0)
    return _y_off + B * (millis() - _t_off) / 1000.0;

  return _y_on + (_power / 255.0 * A + B) * (millis() - _t_on) / 1000.0;
}