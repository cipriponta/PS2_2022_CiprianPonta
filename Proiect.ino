/***********************************************************
 *
 *  PS2_2022_PontaCiprianIoan
 * 
 *  ToDo: EEPROM Library
 * 
 **********************************************************/

#include <LiquidCrystal.h>
#include "src/mcu/adc/ADCModule.h"
#include "src/mcu/uart/UARTModule.h"
#include "src/mcu/timer_pwm/TimerPWMModule.h"
#include "src/mcu/eeprom/EEPROMModule.h"
#include "src/mcu/menu/MenuModule.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
MessageQueue userMessageStorage;
e_Menus currentMenu = MENU_MAIN;

int main()
{
    lcd.begin(16, 2);

    adc_v_init();
    uart_v_init();
    timer_pwm_v_init();

    sei();

    eeprom_v_getStorage();
    uart_v_showUserMessages();

    while (1);
}