#include <stdint.h>
#ifndef SOLENOID_HPP
#define SOLENOID_HPP

class Solenoid
{
    /*
    percuteur : solénoïde qui frappe la balle. Il est contrôlé par un transistor MOSFET qui est lui-même contrôlé par un signal PWM.
    la classe inclue une protection de surchauffe
    */
    public:
        Solenoid(){};
        Solenoid(int pwm_pin);
        ~Solenoid();
        void setPower(uint8_t power);

        void On();
        void Off();
        void run();
        float getWarmup();
        void setMaxDuration(float d_max);//(durée en s)
        void setAvrPower(float avr_power);//(entre 0 et 1)
    private:

      void compute_A_B();
        int _pin;
        float A,B,Tp,r,_avr_power;
        unsigned long _t_on,_t_off,_t_L;
        float _y_on,_y_off;
        uint8_t _state,_prev_state,_power;        
};

#endif