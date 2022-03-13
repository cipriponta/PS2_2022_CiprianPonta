#include <LiquidCrystal.h>
#include "ADCModule.h"
#include "UARTModule.h"
#include "TimerPWMModule.h"

// Change Board to Arduino Mega

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int main()
{
    ADCModule::init();
    UARTModule::init();
    TimerPWMModule::init();
    
    sei();
    
    while(1)
    {
        
    }
}

ISR(TIMER1_COMPA_vect)
{
    UARTModule::println("Hello");
}

