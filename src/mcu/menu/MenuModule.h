#ifndef __MENU_MODULE_H__
#define __MENU_MODULE_H__

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "../adc/ADCModule.h"
#include "../eeprom/EEPROMModule.h"

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
    MENU_MESSAGES_MAXNUM,
    MENU_MESSAGES_UNREAD_SHOW,
    MENU_MESSAGES_READ_SHOW,
    MENU_MESSAGES_DELETE_SHOW,
    MENU_TEMPERATURE_SHOW,
    MENU_MAXNUM
}e_Menus;

extern e_Menus currentMenu;
extern LiquidCrystal lcd;
extern MessageQueue userMessageStorage;
extern void (*menu_v_stateMachine[MENU_MAXNUM][BE_MAXNUM])();
extern int readMessageIndex;

void menu_v_printMenu();

static void menu_v_nothing();
static void menu_v_enterSubmenus();
static void menu_v_enterMainMenu();
static void menu_v_nextSubmenu();
static void menu_v_prevSubmenu();
static void menu_v_enterMsgMenus();
static void menu_v_nextMsgMenu();
static void menu_v_prevMsgMenu();
static void menu_v_enterTempMenu();
static void menu_v_exitTempMenu();
static void menu_v_enterMessUnread();
static void menu_v_exitMessUnread();
static void menu_v_enterMessRead();
static void menu_v_exitMessRead();
static void menu_v_enterMessDelete();
static void menu_v_exitMenuDelete();
static void menu_v_deleteMess();
static void menu_v_nextMessUnread();
static void menu_v_prevMessUnread();
static void menu_v_nextMessRead();
static void menu_v_prevMessRead();

#endif