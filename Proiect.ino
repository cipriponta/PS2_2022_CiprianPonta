/***********************************************************
 *
 *  PS2_2022_PontaCiprianIoan
 *
 **********************************************************/

#include <LiquidCrystal.h>
#include "src/mcu/adc/ADCModule.h"
#include "src/mcu/uart/UARTModule.h"
#include "src/mcu/timer_pwm/TimerPWMModule.h"
#include "src/mcu/eeprom/EEPROMModule.h"


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
MessageQueue userMessageStorage;

int main()
{
    lcd.begin(16, 2);

    adc_v_init();
    uart_v_init();
    timer_pwm_v_init();

    sei();

    userMessageStorage.index = 0;
    eeprom_v_getStorage(&userMessageStorage);
    uart_v_showUserMessages(userMessageStorage);

    while (1);
}

ISR(TIMER5_COMPA_vect)
{
    // Scheduler Interrupt

    // Repeat every 0.1 seconds
    static int interruptCount = 0;
    interruptCount++;
    if(interruptCount == 10)
    {
        interruptCount = 0;
    }

    static int previousStateButtonOk   = 0;
    static int previousStateButtonBack = 0;
    static int previousStateButtonUp   = 0;
    static int previousStateButtonDown = 0;

    int currentStateButtonOk   = PINK & (1 << PK0);
    int currentStateButtonBack = PINK & (1 << PK1);
    int currentStateButtonUp   = PINK & (1 << PK2);
    int currentStateButtonDown = PINK & (1 << PK3);

    if(currentStateButtonOk && !previousStateButtonOk)
    {
        uart_v_stringPrintln("Button Pressed: OK");
        uart_v_emptyPrintln();
    }
    if(currentStateButtonBack && !previousStateButtonBack)
    {
        uart_v_stringPrintln("Button Pressed: Back");
        uart_v_emptyPrintln();
    }
    if(currentStateButtonUp && !previousStateButtonUp)
    {
        uart_v_stringPrintln("Button Pressed: Up");
        uart_v_emptyPrintln();
    }
    if(currentStateButtonDown && !previousStateButtonDown)
    {
        uart_v_stringPrintln("Button Pressed: Down");
        uart_v_emptyPrintln();
    }

    // Repeat every second
    if(interruptCount == 0)
    {
        double temperature = adc_d_readTemperature(0);
        int floodDetected  = PINH & (1 << 6);

        // Display
        lcd.setCursor(0, 0);
        lcd.print("PS2 2022");

        lcd.setCursor(0, 1);
        lcd.print("Temp = " + String(temperature) + "*C    ");

        // Terminal
        // uart_v_stringPrint("Temperature: ");
        // uart_v_doublePrint(temperature);
        // uart_v_emptyPrintln();

        // uart_v_stringPrint("Flood detected: ");
        // if(floodDetected)
        // {
        //     uart_v_stringPrintln("YES");
        // }
        // else
        // {
        //     uart_v_stringPrintln("NO");
        // }
        // uart_v_emptyPrintln();

        // uart_v_emptyPrintln();
    }

    previousStateButtonOk   = currentStateButtonOk;
    previousStateButtonBack = currentStateButtonBack;
    previousStateButtonUp   = currentStateButtonUp;
    previousStateButtonDown = currentStateButtonDown;
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
                uart_v_parseRGB(messageBuffer);
            }
            else if(messageBuffer[0] == '6')
            {
                uart_v_getUserMessage(messageBuffer, &userMessageStorage);
            }
            else if(messageBuffer[0] == '7')
            {
                // Option used for checking the message storage struct

                uart_v_showUserMessages(userMessageStorage);
            }
        }

        messageLength = 0;
    }
    else
    {
        messageBuffer[messageLength++] = character;
    }
}