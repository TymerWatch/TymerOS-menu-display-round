#include "../menu.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "Fonts/FreeMonoBold12pt7b.h"
#include "Fonts/FreeMono12pt7b.h"
#include "../tymer_utils.h"
#include "../tymer_config.h"

Menu::Menu() {
    this->index = -1;
}

Menu::Menu(String name, Arduino_GFX *gfx) {
    this->name = name;
    this->index = 0;
    this->gfx = gfx;
}
/**
 * returns name of the menu
 * @return name of the menu
 */
String Menu::getName() {
    return this->name;
}

/**
 * Returns pointer to the display object
 * @return pointer to TFT_eSPI object
 */
Arduino_GFX *Menu::display() {
    return this->gfx;
}

/**
 * Returns the index of the current item
 * @return index of item
 */
int Menu::getIndex() {
    return this->index;
}
/**
 * Returns number of items in the menu
 * @return number of items
 */
int Menu::numItems() {
    int out = 0;
    for (int i = 0; i < MAX_MENU_ITEMS && this->items[i].getID() > 0; i++) {
        out++;
    }
    return out;
}

/**
 * Returns if menu is selected
 * @return true if menu is selected
 */
MenuItem *Menu::getSelected() {
    return &this->items[index];
}

/**
 * Draws menu on the display
 */
void Menu::draw() {
    int x = MENU_START_COORD_X;
    int y = MENU_START_COORD_Y;
    int angle = MENU_START_ANGLE;
    uint8_t num_items = numItems();
    uint8_t first_elem = (((index - 2) % num_items) + num_items) % num_items;
    //tft->fillScreen(TFT_BLACK);
    int x2, y2;
    for (int i = first_elem, count = 0; count < ITEMS_ON_SCREEN && count < num_items; count++) {
        uint16_t width, height;
        int16_t sx, sy;
        //tft->setTextSize(2);
        gfx->setTextColor(WHITE);
        //Serial.print(items[i].getName() + ": ");
        //Serial.println(width);
        rotate_point(x, y, angle, DP_WIDTH/2, DP_HEIGHT/2, &x2, &y2);
        gfx->setFont(NULL);
        gfx->setTextSize(1);
        gfx->getTextBounds(items[i].getName(), 0, 0, &sx, &sy, &width, &height);
        
        gfx->fillRect(50, y2-(height/2), DP_WIDTH-50, height, BLACK);
        if (items[i].isSelected()) {
            gfx->fillCircle(x2, y2, 4, ORANGE);
        } else {
            gfx->fillCircle(x2, y2, 1, ORANGE);
        }
        gfx->setCursor(x2-width-10, y2-(height/2));
        gfx->print(items[i].getName());
        //gfx->fillRect(0, y, 240, height, BLACK); 
        angle += MENU_STEP_ANGLE;
        i = (((i + 1) % num_items) + num_items) % num_items;
        gfx->setTextSize(1);
        gfx->setFont(NULL);
        
        continue;
    }
}

/**
 * Selects the next item in the menu
 */
void Menu::nextItem() {
    int len = numItems();
    this->items[index].deselect();
    this->index = (((this->index + 1) % len) + len) % len;
    this->items[index].select();
}

/**
 * Selects the previous item in the menu
 */
void Menu::prevItem() {
    int len = numItems();
    this->items[index].deselect();
    this->index = (((this->index - 1) % len) + len) % len;
    this->items[index].select();
}

/**
 * Inserts a new item into the menu
 * @return true if item was added
 */
bool Menu::addItem(MenuItem elem) {
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        if (this->items[i].getID() < 0) {
            this->items[i] = elem;
            return true;
        }
    }
    return false;
}

/**
 * Returns item list
 * @return pointer to item list
 */
MenuItem *Menu::getItems() {
    return this->items;
}

void Menu::setIndex(uint8_t index) {
    this->index = index;
}






MenuItem::MenuItem() {
    this->id = -1;
}


MenuItem::MenuItem(char *name, Menu *parent, Menu *submenu, uint8_t app) {
    this->name = name;
    this->parent = parent;
    this->is_selected = false;
    this->id = 1;
    this->app = app;
    this->submenu = submenu;
}

/**
 * Returns ID of the Item
 * @return ID of the Item
 */
int MenuItem::getID() {
    return this->id;
}

/**
 * Selects the item
 */
void MenuItem::select() {
    this->is_selected = true;
}

/**
 * Deselects the item
 */
void MenuItem::deselect() {
    this->is_selected = false;
}

/**
 * Returns whether the item is selected
 * @return true if item is selected
 */
bool MenuItem::isSelected() {
    return this->is_selected;
}

/**
 * Returns name of the item
 * @return name of the item
 */
String MenuItem::getName() {
    return this->name;
}

/**
 * returns item string depending on the selection
 * @return String representing the item
 */
String MenuItem::toString() {
    return (is_selected ? "> " : "") + this->name;
}

/**
 * Sets new name for the item
 * @param name new name
 */
void MenuItem::setName(char *name) {
    this->name = name;
}

Menu *MenuItem::getSubmenu() {
    return this->submenu;
}

uint8_t MenuItem::getApp() {
    return this->app;
}