#ifndef __MENU_MODULE_H__
#define __MENU_MODULE_H__

#include <Arduino.h>
#include <LiquidCrystal.h>

typedef enum e_ButtonEvents
{
    BE_OK = 0,
    BE_BACK,
    BE_UP,
    BE_DOWN,
    BE_NONE,
    BE_MAXNUM
}e_ButtonEvents;

typedef enum e_Menus
{
    MENU_MAIN = 0,
    MENU_MESSAGES,
    MENU_CONTROL,
    MENU_TEMPERATURE,
    MENU_FLOODS,
    MENU_SUBMENU_MAXNUM,
    MENU_MESSAGES_UNREAD,
    MENU_MESSAGES_READ,
    MENU_MESSAGES_DELETE,
    MENU_MAXNUM
}e_Menus;

extern e_Menus currentMenu;
extern LiquidCrystal lcd;
extern void (*menu_v_stateMachine[MENU_MAXNUM][BE_MAXNUM])();

void menu_v_printMenu();

void menu_v_nothing();
void menu_v_enterSubmenus();
void menu_v_enterMainMenu();
void menu_v_nextSubmenu();
void menu_v_prevSubmenu();


#endif