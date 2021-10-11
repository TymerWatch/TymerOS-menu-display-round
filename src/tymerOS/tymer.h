#ifndef _TYMER_H
#define _TYMER_H

#include "module.h"
#include "menu.h"
#include "button.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <SPI.h>


typedef enum _module_t {
    CLOCK,
    TIMER,
    STOPWATCH,
    HEALTH,
    DEAUTH,
    SETTINGS,
    INFO
} module_t;

class Tymer;

class Tymer {
public:
    Tymer();
    Tymer(Arduino_GFX *gfx, char *ssid, char *pwd);
    void loop();
    Module *getActiveModule();
    void setActiveModule(Module *module);
    Menu *curMenu();
    Menu menu;
private:
    Btn buttons[3];
    uint8_t button_events[3] = {0,0,0};
    Arduino_GFX *gfx;
    Module *activeModule;
    Module *modules[32];
    String ssid, pwd;
    bool inMenu;
    void setup_buttons();
    void setup_wifi();
    void setup_display();
    void setup_menu(char *name);
    void run_module();
    void draw_topbar();
};
#endif /* _TYMER_H */