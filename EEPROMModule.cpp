#include "EEPROMModule.h"

static void EEPROMModule::getStorage(MessageQueue *userMessageStorage)
{
    EEPROM.get(EEPROM_START_ADDRESS, *userMessageStorage);
}

static void EEPROMModule::setStorage(MessageQueue *userMessageStorage)
{
    EEPROM.put(EEPROM_START_ADDRESS, *userMessageStorage);
}