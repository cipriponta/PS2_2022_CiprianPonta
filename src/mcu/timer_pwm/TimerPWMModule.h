#ifndef __TIMER_PWM_MODULE_H__
#define __TIMER_PWM_MODULE_H__

#include <Arduino.h>
#include "../uart/UARTModule.h"

#define F_CPU 16000000LL
#define PRESC 64LL

void timer_pwm_v_init();

#endif