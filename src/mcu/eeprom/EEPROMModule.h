#ifndef __EEPROM_MODULE_H__
#define __EEPROM_MODULE_H__

#include <EEPROM.h>

#define MESSAGE_QUEUE_LENGTH    10
#define MESSAGE_MAX_LENGTH      30
#define EEPROM_START_ADDRESS     0

typedef struct MessageQueue
{
    char messageArray[MESSAGE_QUEUE_LENGTH][MESSAGE_MAX_LENGTH];
    unsigned char readMessagesArray[MESSAGE_QUEUE_LENGTH];
}MessageQueue;

extern MessageQueue userMessageStorage;

void eeprom_v_getStorage();
void eeprom_v_setStorage();
int eeprom_i_checkIfUnread();
int eeprom_i_checkIfRead();

#endif