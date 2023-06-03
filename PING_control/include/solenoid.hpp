#ifndef SOLENOID_HPP
#define SOLENOID_HPP

class Solenoid
{
    /*
    percuteur : solénoïde qui frappe la balle. Il est contrôlé par un transistor MOSFET qui est lui-même contrôlé par un signal PWM.
    la classe inclue une protection de surchauffe : on ne peut pas dépasser Tp secondes à pleine puissance.
    */
    public:
        Solenoid(){};
        Solenoid(int pwm_pin);
        ~Solenoid();
        void setPower(float power);
        int update(unsigned long time);// code de retour : 1 = froid, 0 = OK , -1 = surchauffe
        float getWarmup(){return _warmup;}
    private:
        int _pin;
        float A,B,Tp,r;
        float _warmup,_power,_last_power;
        unsigned long _last_time;
        unsigned long _stop_time;
        
};

#endif