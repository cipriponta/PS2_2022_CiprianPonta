#include "ADCModule.h"

static void ADCModule::init()
{
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
}

static int ADCModule::read(int pin)
{
    ADMUX &= ~0x0F;
    ADMUX |= pin;
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    return ADC;
}