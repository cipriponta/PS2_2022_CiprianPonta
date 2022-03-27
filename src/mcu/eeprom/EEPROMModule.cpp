#include "EEPROMModule.h"

void eeprom_v_getStorage(MessageQueue *userMessageStorage)
{
    EEPROM.get(EEPROM_START_ADDRESS, *userMessageStorage);
}

void eeprom_v_setStorage(MessageQueue *userMessageStorage)
{
    EEPROM.put(EEPROM_START_ADDRESS, *userMessageStorage);
}