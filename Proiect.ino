/***********************************************************
 *  
 *  PS2_2022_PontaCiprianIoan
 *  ToDo: Menu
 *
 **********************************************************/

#include <LiquidCrystal.h>
#include "ADCModule.h"
#include "UARTModule.h"
#include "TimerPWMModule.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int main()
{
    lcd.begin(16, 2);
    
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
    static int interruptCount = 0;
    
    interruptCount++;
    
    if(interruptCount == 5)
    {
        interruptCount = 0;
    }
    
    if(interruptCount == 0)
    {
        lcd.setCursor(0, 0);
        lcd.print("PS2 2022");

        double temperature = ADCModule::readTemperature(0);
        
        lcd.setCursor(0, 1);
        lcd.print("Temp = " + String(temperature) + "*C    ");
    }
}