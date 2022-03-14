#ifndef __ADC_MODULE_H__
#define __ADC_MODULE_H__

#include <Arduino.h>

class ADCModule
{
public:
    static void init();
    static int read(int pin);
    static double readTemperature(int pin);
};

#endif