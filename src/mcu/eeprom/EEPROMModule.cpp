#include "EEPROMModule.h"

void eeprom_v_getStorage()
{
    EEPROM.get(EEPROM_START_ADDRESS, userMessageStorage);
}

void eeprom_v_setStorage()
{
    EEPROM.put(EEPROM_START_ADDRESS, userMessageStorage);
}

int eeprom_i_checkIfUnread()
{
    for(int i = 0; i < MESSAGE_QUEUE_LENGTH; i++)
    {
        if(userMessageStorage.readMessagesArray[i] == 0)
        {
            return 1;
        }
    }
    return 0;
}

int eeprom_i_checkIfRead()
{
    for(int i = 0; i < MESSAGE_QUEUE_LENGTH; i++)
    {
        if(userMessageStorage.readMessagesArray[i] == 1)
        {
            return 1;
        }
    }
    return 0;
}