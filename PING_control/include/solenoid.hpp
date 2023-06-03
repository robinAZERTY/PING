#ifndef SOLENOID_HPP
#define SOLENOID_HPP

class solenoid
{
    /*
    percuteur : solénoïde qui frappe la balle. Il est contrôlé par un transistor MOSFET qui est lui-même contrôlé par un signal PWM.
    la classe inclue une protection de surchauffe : on ne peut pas dépasser Tp secondes à pleine puissance.
    */
    public:
        solenoid(int pwm_pin, float *power_ptr);
        ~solenoid();
        int update(unsigned long time);
        float getWarmup(){return _warmup;}
    private:
        int _pin;
        float A,B,Tp,r;
        float _warmup,*_power,_last_power;
        unsigned long _last_time;
};

#endif