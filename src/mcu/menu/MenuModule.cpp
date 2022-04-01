#include "MenuModule.h"

void (*menu_v_stateMachine[MENU_MAXNUM][BE_MAXNUM])() = 
{
    //  OK                      BACK                    UP                      DOWN                    NONE
    {   menu_v_enterSubmenus,   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // MENU_MAIN
    {   menu_v_enterMsgMenus,   menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing          },       // MENU_MESSAGES
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing          },       // MENU_CONTROL
    {   menu_v_enterTempMenu,   menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing          },       // MENU_TEMPERATURE
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing          },       // MENU_FLOODS
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // -- MENU_SUBMENU_MAXNUM --
    {   menu_v_enterMessUnread, menu_v_enterSubmenus,   menu_v_prevMsgMenu,     menu_v_nextMsgMenu,     menu_v_nothing          },       // MENU_MESSAGES_UNREAD
    {   menu_v_enterMessRead,   menu_v_enterSubmenus,   menu_v_prevMsgMenu,     menu_v_nextMsgMenu,     menu_v_nothing          },       // MENU_MESSAGES_READ 
    {   menu_v_enterMessDelete, menu_v_enterSubmenus,   menu_v_prevMsgMenu,     menu_v_nextMsgMenu,     menu_v_nothing          },       // MENU_MESSAGES_DELETE
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // -- MENU_MESSAGES_MAXNUM --
    {   menu_v_nothing,         menu_v_exitMessUnread,  menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // MENU_MESSAGES_UNREAD_SHOW
    {   menu_v_nothing,         menu_v_exitMessRead,    menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // MENU_MESSAGES_READ_SHOW
    {   menu_v_deleteMess,      menu_v_exitMenuDelete,  menu_v_nothing,         menu_v_nothing,         menu_v_nothing          },       // MENU_MESSAGES_DELETE_SHOW
    {   menu_v_exitTempMenu,    menu_v_exitTempMenu,    menu_v_nothing,         menu_v_nothing,         menu_v_enterTempMenu    }        // MENU_TEMPERATURE_SHOW
};

static int unreadMessageIndex = MESSAGE_QUEUE_LENGTH - 1;
static int readMessageIndex = MESSAGE_QUEUE_LENGTH - 1;

void menu_v_printMenu()
{
    double temperature;

    switch(currentMenu)
    {
        case MENU_MAIN:
            lcd.setCursor(0, 0);
            lcd.write("PS2 2022         ");
            lcd.setCursor(0, 1);
            lcd.write("Press OK         ");
        break;
        case MENU_MESSAGES:
            lcd.setCursor(0, 0);
            lcd.write("Choose Menu:     ");
            lcd.setCursor(0, 1);
            lcd.write("Messages         ");
        break;
        case MENU_CONTROL:
            lcd.setCursor(0, 0);
            lcd.write("Choose Menu:     ");
            lcd.setCursor(0, 1);
            lcd.write("Control          ");
        break;
        case MENU_TEMPERATURE:
            lcd.setCursor(0, 0);
            lcd.write("Choose Menu:     ");
            lcd.setCursor(0, 1);
            lcd.write("Temperature      ");
        break;
        case MENU_FLOODS:
            lcd.setCursor(0, 0);
            lcd.write("Choose Menu:     ");
            lcd.setCursor(0, 1);
            lcd.write("Floods           ");
        break;
        case MENU_MESSAGES_UNREAD:
            lcd.setCursor(0, 0);
            lcd.write("Messages Menu:   ");
            lcd.setCursor(0, 1);
            lcd.write("Unread Messages  ");
        break;
        case MENU_MESSAGES_READ:
            lcd.setCursor(0, 0);
            lcd.write("Messages Menu:   ");
            lcd.setCursor(0, 1);
            lcd.write("Read Messages    ");
        break;
        case MENU_MESSAGES_DELETE:
            lcd.setCursor(0, 0);
            lcd.write("Messages Menu:   ");
            lcd.setCursor(0, 1);
            lcd.write("Delete Messages  ");
        break;
        case MENU_TEMPERATURE_SHOW:
            lcd.setCursor(0, 0);
            lcd.write("Temperature Menu:");
            temperature = adc_d_readTemperature(0);
            lcd.setCursor(0, 1);
            lcd.print(String(temperature) + " *C     ");
        break;
        case MENU_MESSAGES_UNREAD_SHOW:
            lcd.setCursor(0, 0);
            lcd.write("Unread Messages:");
            lcd.setCursor(0, 1);
            lcd.write("                ");
        break;
        case MENU_MESSAGES_READ_SHOW:
            lcd.setCursor(0, 0);
            lcd.write("Read Messages:  ");
            lcd.setCursor(0, 1);
            lcd.write("                ");
        break;
        case MENU_MESSAGES_DELETE_SHOW:
            lcd.setCursor(0, 0);
            lcd.write("Delete Messages:");
            lcd.setCursor(0, 1);
            lcd.write("Press OK        ");
        break;
    }
}

static void menu_v_nothing()
{
    return;
}

static void menu_v_enterSubmenus()
{
    currentMenu = MENU_MESSAGES;
}

static void menu_v_enterMainMenu()
{
    currentMenu = MENU_MAIN;
}

static void menu_v_nextSubmenu()
{
    currentMenu = currentMenu + 1;
    if(currentMenu == MENU_SUBMENU_MAXNUM)
    {
        currentMenu = MENU_MAIN + 1;
    }
}

static void menu_v_prevSubmenu()
{
    currentMenu = currentMenu - 1;
    if(currentMenu == MENU_MAIN)
    {
        currentMenu = MENU_SUBMENU_MAXNUM - 1;
    }
}

static void menu_v_enterMsgMenus()
{
    currentMenu = MENU_MESSAGES_UNREAD;
}

static void menu_v_nextMsgMenu()
{
    currentMenu = currentMenu + 1;
    if(currentMenu == MENU_MESSAGES_MAXNUM)
    {
        currentMenu = MENU_SUBMENU_MAXNUM + 1;
    }
}

static void menu_v_prevMsgMenu()
{
    currentMenu = currentMenu - 1;
    if(currentMenu == MENU_SUBMENU_MAXNUM)
    {
        currentMenu = MENU_MESSAGES_MAXNUM - 1;
    }
}

static void menu_v_enterTempMenu()
{
    currentMenu = MENU_TEMPERATURE_SHOW;
}

static void menu_v_exitTempMenu()
{
    currentMenu = MENU_TEMPERATURE;
}

static void menu_v_enterMessUnread()
{
    currentMenu = MENU_MESSAGES_UNREAD_SHOW;
}

static void menu_v_exitMessUnread()
{
    currentMenu = MENU_MESSAGES_UNREAD;
}

static void menu_v_enterMessRead()
{
    currentMenu = MENU_MESSAGES_READ_SHOW;
}

static void menu_v_exitMessRead()
{
    currentMenu = MENU_MESSAGES_READ;
}

static void menu_v_enterMessDelete()
{
    currentMenu = MENU_MESSAGES_DELETE_SHOW;
}

static void menu_v_exitMenuDelete()
{
    currentMenu = MENU_MESSAGES_DELETE;
}

static void menu_v_deleteMess()
{
    for(int i = MESSAGE_QUEUE_LENGTH - 1; i >= 0; i--)
    {
        strcpy(userMessageStorage.messageArray[i], "");
    }
    eeprom_v_setStorage();
    menu_v_exitMenuDelete();
}