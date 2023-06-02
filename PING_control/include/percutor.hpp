#ifndef PERCUTOR_HPP
#define PERCUTOR_HPP

class percutor
{
    /*
    percuteur : solénoïde qui frappe la balle. Il est contrôlé par un transistor MOSFET qui est lui-même contrôlé par un signal PWM.
    la classe inclue une protection de surchauffe : on ne peut pas dépasser Tp secondes à pleine puissance.
    */
    public:
        percutor(int pwm_pin, float *power_ptr);
        ~percutor();
        int update(unsigned long time);
        float getWarmup(){return _warmup;}
    private:
        int _pin;
        float A,B,Tp,T,r;
        float _warmup,*_power;
        unsigned long _last_time;
};

#endif