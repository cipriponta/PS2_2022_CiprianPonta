#ifndef __TIMER_PWM_MODULE_H__
#define __TIMER_PWM_MODULE_H__

#include <Arduino.h>
#include "UARTModule.h"

#define F_CPU 16000000LL
#define PRESC 64LL

class TimerPWMModule
{
public:
    static void init();
};

#endif