/***********************************************************
 *  
 *  PS2_2022_PontaCiprianIoan
 *
 **********************************************************/

#include <LiquidCrystal.h>
#include "ADCModule.h"
#include "UARTModule.h"
#include "TimerPWMModule.h"
#include "EEPROMModule.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
MessageQueue userMessageStorage;

int main()
{
    lcd.begin(16, 2);
    
    ADCModule::init();
    UARTModule::init();
    TimerPWMModule::init();
    
    sei();
    
    userMessageStorage.index = 0;
    EEPROMModule::getStorage(&userMessageStorage);
    UARTModule::showUserMessages(userMessageStorage);
    
    while(1)
    {
        
    }
}

ISR(TIMER5_COMPA_vect)
{   
    // Scheduler Interrupt

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

ISR(USART0_RX_vect)
{
    // Reception Interrupt
    
    static char messageBuffer[100];
    static int messageLength;
    
    char character = UDR0;
    
    if(character == '\n')
    {
        messageBuffer[messageLength] = '\0';  
        
        /* Used for debugging */
        // for(int i = 0; i < strlen(messageBuffer); i++)
        // {
            // UARTModule::sendChar(messageBuffer[i]);
        // }
        
        if(strcmp(messageBuffer, "1 A") == 0)
        {
            PORTB |= (1 << PB7);
        }
        else if(strcmp(messageBuffer, "1 S") == 0)
        {
            PORTB &= !(1 << PB7);
        }
        else if(strlen(messageBuffer) >= 1)
        {
            if(messageBuffer[0] == '2')
            {
                UARTModule::parseRGB(messageBuffer);
            }
            else if(messageBuffer[0] == '6')
            {
                UARTModule::getUserMessage(messageBuffer, &userMessageStorage);
            }
            else if(messageBuffer[0] == '7')
            {
                // Option used for checking the message storage struct 
                
                UARTModule::showUserMessages(userMessageStorage);
            }
        }
        
        messageLength = 0;
    }
    else
    {
        messageBuffer[messageLength++] = character;
    }
}