#ifndef __ADC_MODULE_H__
#define __ADC_MODULE_H__

#include <Arduino.h>

void adc_v_init();
static int adc_i_read(int pin);
double adc_d_readTemperature(int pin);

#endif