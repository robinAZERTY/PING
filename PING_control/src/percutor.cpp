#include "percutor.hpp"
#include "Arduino.h"

percutor::percutor(int pwm_pin, float *power_ptr)
{
    //parametres par défaut du modèle thermique
    Tp = 5.0;
    r = 0.2; // full power 20% of the time max

    //calculs des coefficients
    T = Tp/r;
    B = -1.0/(T-Tp);//coefficient de la dissipation thermique
    A = 1/Tp - B; //coefficient de la montée en température  
    
    //initialisation
    _power = power_ptr;
    _warmup = 0.0;
    _pin = pwm_pin;
    pinMode(_pin, OUTPUT);
    analogWriteResolution(8);
    analogWrite(_pin, 0);
}

percutor::~percutor()
{
}

int percutor::update(unsigned long time)
{
    if (*_power > 1.0)
        *_power = 1.0;
    else if (*_power < 0.0)
        *_power = 0.0;

    int ret=0; // code de retour : 1 = froid, 0 = OK , -1 = surchauffe

    float dt = (time - _last_time)/1000.0;
    _warmup += (A**_power + B)*dt;

    if (_warmup >= 1.0)// risque de surchauffe
    {
        _warmup = 1.0;
        *_power = 0.0;// on désactive le solénoïde
        ret = -1;
    }
    else if (_warmup < 0.0)
    {
        _warmup = 0.0;
        ret = 1;  
    }

    analogWrite(_pin, 255**_power);
    _last_time = time;

    return ret;
}