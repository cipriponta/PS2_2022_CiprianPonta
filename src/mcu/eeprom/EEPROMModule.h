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

void eeprom_v_getStorage(MessageQueue *userMessageStorage);
void eeprom_v_setStorage(MessageQueue *userMessageStorage);

#endif