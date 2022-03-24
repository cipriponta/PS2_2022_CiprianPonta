#ifndef __UART_MODULE_H__
#define __UART_MODULE_H__

#include <Arduino.h>
#include "EEPROMModule.h"

class UARTModule
{
public: 
    static void init();
    
    static void sendChar(char message);
    static void print(char *message);
    static void print(int number);
    static void print(double number);
    static void println();
    static void println(char *message);
    
    static int  checkIfHex(char c);
    static void parseRGB(char *message);
    
    static void getUserMessage(char *message, MessageQueue *userMessageStorage);
    static void showUserMessages(MessageQueue userMessageStorage);
};

#endif