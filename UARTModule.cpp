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

static void UARTModule::print(double number)
{
    double numberX100 = number * 100;
    int decimalPart = (int)(numberX100 / 100.0);
    int fractionalPart = (int)numberX100 % 100;
    
    UARTModule::print(decimalPart);
    UARTModule::print(".");
    UARTModule::print(fractionalPart);
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

static void UARTModule::getUserMessage(char *message, MessageQueue *userMessageStorage)
{
    UARTModule::print("Message received: ");
    UARTModule::println(message + 2);
    UARTModule::println();
    
    userMessageStorage->index++;
    if(userMessageStorage->index == 10)
    {
        userMessageStorage->index = 0;
    }
    
    strcpy(userMessageStorage->messageArray[userMessageStorage->index], message + 2);
    
    EEPROMModule::setStorage(userMessageStorage);
}

static void UARTModule::showUserMessages(MessageQueue userMessageStorage)
{
    int count = 10;
    
    UARTModule::println("Last 10 User Messages: ");
    for(int i = userMessageStorage.index; i >= 0; i--)
    {
        UARTModule::print(count--);
        UARTModule::print(". \t");
        UARTModule::println(userMessageStorage.messageArray[i]);
    }
    
    for(int i = MESSAGE_QUEUE_LENGTH - 1; i > userMessageStorage.index; i--)
    {
        UARTModule::print(count--);
        UARTModule::print(". \t");
        UARTModule::println(userMessageStorage.messageArray[i]);
    }
    
    UARTModule::println();
}