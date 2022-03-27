#include "ADCModule.h"

void adc_v_init()
{
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
}

static int adc_i_read(int pin)
{
    ADMUX &= ~0x0F;
    ADMUX |= pin;
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    return ADC;
}

double adc_d_readTemperature(int pin)
{
    int adcValue = adc_i_read(pin);
    double voltage = 5.0/1023.0 * (double)adcValue;
	return voltage * 100.0;
}