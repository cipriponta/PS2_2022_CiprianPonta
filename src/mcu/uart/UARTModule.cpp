#include "UARTModule.h"

void uart_v_init()
{
    UBRR0 = 103;                             // 9600 Baud Rate
    UCSR0B |= (1 << RXCIE0);                 // receiver interrupt enable
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // receiver and transmitter functionalities
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bit data
}

static void uart_v_sendChar(char message)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = message;
}

void uart_v_stringPrint(char *message)
{
    for (int i = 0; i < strlen(message); i++)
    {
        uart_v_sendChar(message[i]);
    }
}

void uart_v_emptyPrintln()
{
    uart_v_sendChar('\n');
}

void uart_v_stringPrintln(char *message)
{
    for (int i = 0; i < strlen(message); i++)
    {
        uart_v_sendChar(message[i]);
    }
    uart_v_sendChar('\n');
}


void uart_v_intPrint(int number)
{
    char charNumber[10];

    itoa(number, charNumber, 10);

    uart_v_stringPrint(charNumber);
}

void uart_v_doublePrint(double number)
{
    double numberX100 = number * 100;
    int decimalPart = (int)(numberX100 / 100.0);
    int fractionalPart = ((int)numberX100) % 100;


    uart_v_intPrint(decimalPart);
    uart_v_stringPrint(".");
    uart_v_intPrint(fractionalPart);
}

int uart_i_checkIfHex(char c)
{
    return (c == '0') || (c == '1') || (c == '2') || (c == '3') ||
            (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
            (c == '8') || (c == '9') || (c == 'a') || (c == 'b') ||
            (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f');
}

void uart_v_parseRGB(char *message)
{
    for (int i = 2; i < strlen(message); i++)
    {
        if (!uart_i_checkIfHex(tolower(message[i])))
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
}

void uart_v_getUserMessage(char *message)
{
    uart_v_stringPrint("Message received: ");
    uart_v_stringPrintln(message + 2);
    uart_v_emptyPrintln();
    
    for(int i = 0; i <= MESSAGE_QUEUE_LENGTH - 2; i++)
    {
        strcpy(userMessageStorage.messageArray[i], userMessageStorage.messageArray[i + 1]);
    }

    strcpy(userMessageStorage.messageArray[MESSAGE_QUEUE_LENGTH - 1], message + 2);
    userMessageStorage.readMessagesArray[MESSAGE_QUEUE_LENGTH - 1] = 0;

    eeprom_v_setStorage();
}

void uart_v_showUserMessages()
{
    uart_v_stringPrintln("Last 10 User Messages: ");
    for(int i = MESSAGE_QUEUE_LENGTH - 1; i >= 0; i--)
    {
        uart_v_intPrint((int)(i + 1));
        uart_v_stringPrint(".");
        if(userMessageStorage.readMessagesArray[i] == 1)
        {
            uart_v_stringPrint("(R)");
        }
        else
        {
            uart_v_stringPrint("(U)");
        }
        uart_v_stringPrint("\t");
        uart_v_stringPrintln(userMessageStorage.messageArray[i]);
    }
    uart_v_emptyPrintln();
}

ISR(USART0_RX_vect)
{
    // Reception Interrupt
    cli();
    
    static volatile char messageBuffer[100];
    static volatile int messageLength;

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
                uart_v_getUserMessage(messageBuffer);
            }
            else if(messageBuffer[0] == '7')
            {
                // Option used for checking the message storage struct

                uart_v_showUserMessages();
            }
        }

        messageLength = 0;
    }
    else
    {
        messageBuffer[messageLength++] = character;
    }

    sei();
}