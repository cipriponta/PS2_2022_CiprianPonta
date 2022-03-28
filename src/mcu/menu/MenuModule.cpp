#include "MenuModule.h"

void (*menu_v_stateMachine[MENU_MAXNUM][BE_MAXNUM])() = 
{
    //  OK                      BACK                    UP                      DOWN                    NONE
    {   menu_v_enterSubmenus,   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing  },       // MENU_MAIN
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing  },       // MENU_MESSAGES
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing  },       // MENU_CONTROL
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing  },       // MENU_TEMPERATURE
    {   menu_v_nothing,         menu_v_enterMainMenu,   menu_v_prevSubmenu,     menu_v_nextSubmenu,     menu_v_nothing  },       // MENU_FLOODS
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing  },       // -- MENU_SUBMENU_MAXNUM --
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing  },       // MENU_MESSAGES_UNREAD
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing  },       // MENU_MESSAGES_READ 
    {   menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing,         menu_v_nothing  },       // MENU_MESSAGES_DELETE
};

void menu_v_printMenu()
{
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
            lcd.write("TO DO            ");
            lcd.setCursor(0, 1);
            lcd.write("                 ");
        break;
        case MENU_MESSAGES_READ:
            lcd.setCursor(0, 0);
            lcd.write("TO DO             ");
            lcd.setCursor(0, 1);
            lcd.write("                  ");
        break;
        case MENU_MESSAGES_DELETE:
            lcd.setCursor(0, 0);
            lcd.write("TO DO             ");
            lcd.setCursor(0, 1);
            lcd.write("                  ");
        break;
    }
}

void menu_v_nothing()
{
    return;
}

void menu_v_enterSubmenus()
{
    currentMenu = MENU_MESSAGES;
}

void menu_v_enterMainMenu()
{
    currentMenu = MENU_MAIN;
}

void menu_v_nextSubmenu()
{
    currentMenu = currentMenu + 1;
    if(currentMenu == MENU_SUBMENU_MAXNUM)
    {
        currentMenu = MENU_MAIN + 1;
    }
}

void menu_v_prevSubmenu()
{
    currentMenu = currentMenu - 1;
    if(currentMenu == MENU_MAIN)
    {
        currentMenu = MENU_SUBMENU_MAXNUM - 1;
    }
}