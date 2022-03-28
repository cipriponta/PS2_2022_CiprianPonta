#ifndef __TIMER_PWM_MODULE_H__
#define __TIMER_PWM_MODULE_H__

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../uart/UARTModule.h"
#include "../adc/ADCModule.h"
#include "../menu/MenuModule.h"

#define F_CPU 16000000LL
#define PRESC 64LL

extern LiquidCrystal lcd;
extern e_Menus currentMenu;

void timer_pwm_v_init();

#endif