#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "module.h"

#define MAX_MENU_ITEMS  32
#define ITEMS_ON_SCREEN 5

class Menu;
class MenuItem;

class MenuItem {
public:
    MenuItem();
    MenuItem(char *name, Menu *parent, Menu *submenu, uint8_t app);
    int getID();
    void select();
    void deselect();
    bool isSelected();
    String getName();
    String toString();
    void setName(char *name);
    Menu *getSubmenu();
    uint8_t getApp();
private:
    Menu *parent;
    String name;
    bool is_selected;
    int id;
    Menu *submenu;
    uint8_t app;
};

class Menu {
public:
    Menu(String name, Arduino_GFX *gfx);
    Menu();
    String getName();
    Arduino_GFX *display();
    int getIndex();
    int numItems();
    MenuItem *getSelected();
    void draw();
    void nextItem();
    void prevItem();
    bool addItem(MenuItem item);
    void setIndex(uint8_t index);
    MenuItem *getItems();
    MenuItem items[MAX_MENU_ITEMS];
private:
    //MenuItem items[MAX_MENU_ITEMS];
    Arduino_GFX *gfx;
    String name;
    int index;
    bool is_selected;
};
#endif