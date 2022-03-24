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
    
    if(interruptCount == 10)
    {
        interruptCount = 0;
    }
    
    if(interruptCount == 0)
    {
        double temperature = ADCModule::readTemperature(0);
        int floodDetected = PINH & (1 << 6);
        
        // Display
        lcd.setCursor(0, 0);
        lcd.print("PS2 2022");  
        
        lcd.setCursor(0, 1);
        lcd.print("Temp = " + String(temperature) + "*C    ");
        
        // Terminal
        UARTModule::print("Temperature: ");
        UARTModule::print(temperature);
        UARTModule::println();
        
        UARTModule::print("Flood detected: ");
        if(floodDetected)
        {
            UARTModule::println("YES");
        }  
        else
        {
            UARTModule::println("NO");
        }
        UARTModule::println();
        
        UARTModule::println();
    }
}