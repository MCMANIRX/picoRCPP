#include "inc/PWMModule.h"
#include <cmath>

PWMModule::PWMModule(int A_pin, int B_pin, long freq, long clk_sys):

        A_pin(A_pin),
        B_pin(B_pin),
        freq(freq),
        clk_sys(clk_sys) 
        
        {

            this->mclass = Module::MOTOR_DRIVE;

        }


 void PWMModule::stopMotors() {

    pwm_set_gpio_level(A_pin,0);
    pwm_set_gpio_level(B_pin,0);

 }


void PWMModule::setSpeed(int speed) {

    if (abs(speed) < thresh) {

        pwm_set_gpio_level(A_pin,0);
        pwm_set_gpio_level(B_pin,0);      
    }

    else if(speed > 0) {

        pwm_set_gpio_level(A_pin, abs(speed));
        pwm_set_gpio_level(B_pin,0);
    }
        else {

        pwm_set_gpio_level(B_pin, abs(speed));
        pwm_set_gpio_level(A_pin,0);
    }

 }




