#pragma once
#include "Module.h"
#include "hardware/pwm.h"
#include <cstdint>

class PWMModule : public Module {

    long freq = 1000;
    int A_pin = -1;
    int B_pin = -1;
    int wrap = 0;
    int level = 1;
    int thresh = 20;
    long clk_sys = 125000000;


        inline int get_wrap(long clk_sys, long freq){

            wrap =  (int)((clk_sys/freq)-1);

            if(wrap > UINT16_MAX){
                return Module::FAIL;
            }

            return wrap;
        }



        inline int init_pwm(uint pin, long clk_sys) {


            int slice = pwm_gpio_to_slice_num(pin);

            if(get_wrap(clk_sys, freq)!=Module::FAIL)
                pwm_set_wrap(slice,wrap);
            else    
                return Module::FAIL;
                
            gpio_set_function(pin, GPIO_FUNC_PWM);
            pwm_set_enabled(slice, true);
            pwm_set_gpio_level(pin,0);

            return Module::OK;

        }


        int _init () {

            if(get_wrap(clk_sys, freq)==Module::FAIL)
                return Module::FAIL;

            if(init_pwm(A_pin,clk_sys) + init_pwm(B_pin,clk_sys))
                return Module::FAIL;

            return Module::OK;
        }


    public:

        PWMModule(int A_pin, int B_pin,long freq=1000, long clk_sys=125000000);

        void stopMotors();
        void setSpeed(int speed);


        virtual bool enable() {

            this->setEnabled(init());
            return this->isEnabled();

        }

        virtual bool disable() {

            this->stopMotors();
            pwm_set_enabled(pwm_gpio_to_slice_num(A_pin),false);
            pwm_set_enabled(pwm_gpio_to_slice_num(B_pin),false);
            this->setEnabled(false);

            return this->isEnabled();

        } 

        virtual void update(){

        }

        virtual int init() {

            return _init();
        }



};

