#ifndef __UART_MODULE_H__
#define __UART_MODULE_H__

#include <Arduino.h>
#include "../eeprom/EEPROMModule.h"

extern MessageQueue userMessageStorage;

void uart_v_init();

static void uart_v_sendChar(char message);
void uart_v_stringPrint(char *message);
void uart_v_emptyPrintln();
void uart_v_stringPrintln(char *message);
void uart_v_intPrint(int number);
void uart_v_doublePrint(double number);

int  uart_i_checkIfHex(char c);
void uart_v_parseRGB(char *message);

void uart_v_getUserMessage(char *message, MessageQueue *userMessageStorage);
void uart_v_showUserMessages(MessageQueue userMessageStorage);

#endif