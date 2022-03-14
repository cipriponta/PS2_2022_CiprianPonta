#include "UARTModule.h"

static void UARTModule::init()
{
    UBRR0 = 103;                            // 9600 Baud Rate
    UCSR0B |= (1<<RXCIE0);                  // receiver interrupt enable
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);      // receiver and transmitter functionalities
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);    // 8 bit data
}

static void UARTModule::sendChar(char message)
{
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = message;
}

static void UARTModule::print(char *message)
{
    for(int i = 0; i < strlen(message); i++)
    {
        UARTModule::sendChar(message[i]);
    }
}

static void UARTModule::print(int number)
{
    char charNumber[10];
    
    itoa(number, charNumber, 10);
    
    UARTModule::print(charNumber);
}

static void UARTModule::println()
{
    UARTModule::sendChar('\n');
}

static void UARTModule::println(char *message)
{
    for(int i = 0; i < strlen(message); i++)
    {
        UARTModule::sendChar(message[i]);
        
    }
    UARTModule::sendChar('\n');
}

static int UARTModule::checkIfHex(char c)
{
    return  (c == '0') || (c == '1') || (c == '2') || (c == '3') ||
            (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
            (c == '8') || (c == '9') || (c == 'a') || (c == 'b') ||
            (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f');
}

static void UARTModule::parseRGB(char *message)
{
    for(int i = 2; i < strlen(message); i++)
    {
        if(!checkIfHex(tolower(message[i])))
        {
            return;
        }
    }
    
    char charOCR1B[3];
    char charOCR1A[3];
    char charOCR2A[3];
    
    strncpy(charOCR1B, message + 2, 2);
    charOCR1B[2] = '\0';
    strncpy(charOCR1A, message + 4, 2);
    charOCR1A[2] = '\0';
    strncpy(charOCR2A, message + 6, 2);
    charOCR1A[2] = '\0';
    
    OCR1B = (int)strtol(charOCR1B, NULL, 16);
    OCR1A = (int)strtol(charOCR1A, NULL, 16);
    OCR2A = (int)strtol(charOCR2A, NULL, 16);
    
    /* Used for debugging */
    // UARTModule::print("(");
    // UARTModule::print((int)OCR1B);
    // UARTModule::print(", ");
    // UARTModule::print((int)OCR1A);
    // UARTModule::print(", ");
    // UARTModule::print((int)OCR2A);
    // UARTModule::println(")");
}

ISR(USART0_RX_vect)
{
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
        else if(strlen(messageBuffer) == 8)
        {
            if(messageBuffer[0] == '2')
            {
                UARTModule::parseRGB(messageBuffer);
            }
        }
        
        messageLength = 0;
    }
    else
    {
        messageBuffer[messageLength++] = character;
    }
}