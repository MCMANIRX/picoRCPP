#pragma once
#include "pico/stdlib.h"

class Module
{
    private:
        bool enabled = false;

    public:

        enum module_class {
            NONE,
            MOTOR_DRIVE,
            IMU,
            BATTERY_MONITOR   
        };

        enum status {

            OK,
            FAIL = -1

        };

        module_class mclass = Module::NONE;


        Module(){}
        ~Module();

        virtual void update() = 0;
        virtual bool enable() = 0;
        virtual bool disable() = 0;
    ///    virtual int init() = 0;

        bool isEnabled() const;
        void setEnabled(bool on);

};

