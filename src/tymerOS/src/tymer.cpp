#include "../tymer.h"
#include "../menu.h"
#include "../module.h"
#include "../tymer_config.h"
#include "../modules/clock.h"
#include <Arduino.h>
#include <WiFi.h>
//#include <Fonts/FreeMono12pt7b.h>
#include <Arduino_GFX_Library.h>
#include "Fonts/FreeMonoBold9pt7b.h"

Clock *clock_app;

Tymer::Tymer() {

}

Tymer::Tymer(Arduino_GFX *gfx, char *ssid, char *pwd) {
    this->gfx = gfx;
    this->ssid = ssid;
    this->pwd = pwd;
    clock_app = new Clock();
    //setup_buttons();
    setup_display();
    //setup_wifi();
    setup_menu("Main");
}

Module *Tymer::getActiveModule() {
    return activeModule;
}

void Tymer::setup_buttons() {

    buttons[0] = Btn(BTN_UP);
    buttons[1] = Btn(BTN_DOWN);
    buttons[2] = Btn(BTN_SELECT);
    //buttons[3] = Btn(BUTTON_FN);
}

void Tymer::setup_display() {
    gfx->begin();
    gfx->invertDisplay(true);
    gfx->setRotation(2);
    gfx->setTextSize(1);
    gfx->fillScreen(BLACK);
}

void Tymer::setup_wifi() {
    //tft->unloadFont();
    Serial.println("======| WiFi Config |======");
    WiFi.begin(this->ssid.c_str(), this->pwd.c_str()); 
    int count = 0;
    Serial.print("Connecting to " + this->ssid);
    while (WiFi.status() != WL_CONNECTED) {
        if (count == WIFI_TIMEOUT) {
            WiFi.disconnect();
            Serial.println("\nConnection failed...");
            Serial.println("Continuing...");
            delay(1000);
            return;
        }
        Serial.print(".");
        count++;
        delay(500);
    }
    Serial.println("\n\nConnected...");     
    delay(1000);
}

void Tymer::setup_menu(char *name) {
    this->menu = Menu("Main", gfx);
    modules[CLOCK] = clock_app;
    menu.addItem(MenuItem("Clock", &menu, NULL, CLOCK));
    static_cast<Clock*>(modules[CLOCK])->setTime(7,35);

    menu.items[0].select();

    //modules[TIMER] = Module("Timer");
    menu.addItem(MenuItem("Timer", &menu, NULL, TIMER));

    //modules[STOPWATCH] = Module("Stopwatch");
    menu.addItem(MenuItem("Stopwatch", &menu, NULL, STOPWATCH));

    //modules[HEALTH] = Module("Health");
    menu.addItem(MenuItem("Health", &menu, NULL, HEALTH));

    //modules[DEAUTH] = Module("Deauth");
    menu.addItem(MenuItem("Deauth", &menu, NULL,DEAUTH)); 

    //modules[SETTINGS] = Module("Settings");
    menu.addItem(MenuItem("Settings", &menu, NULL, SETTINGS));

    //modules[INFO] = Module("Info");
    menu.addItem(MenuItem("Info", &menu, NULL, INFO));
    activeModule = modules[CLOCK];
    inMenu = false;
}

void Tymer::run_module() {
    if (activeModule != NULL) {
        activeModule->draw(gfx);
    }
}

void Tymer::draw_topbar() {
    int16_t x1,y1;
    uint16_t w,h;
    //gfx->drawFastHLine(0, 30, 240, WHITE);
    gfx->fillRect(DP_ORIGIN, DP_WIDTH, TOP_BAR_HEIGHT, WHITE);
    gfx->setTextSize(1);
    gfx->setTextColor(BLACK);
    gfx->setFont(&FreeMonoBold9pt7b);
    gfx->getTextBounds("13:37", DP_ORIGIN, &x1, &y1, &w, &h);
    gfx->setCursor((DP_WIDTH/2)-(w/2), 14);
    gfx->print("13:37");
    gfx->setFont(NULL);
    gfx->setTextColor(WHITE);
    gfx->setCursor(25, 55);
    gfx->print("up");
    gfx->setCursor(25, 185);
    gfx->print("down");
}


void Tymer::loop() {
    //Serial.printf("up:%d  down:%d  select:%d\r", button_events[0], button_events[1], button_events[2]);
    //uint8_t events[3] = {0,0,0};
    //buttons[0].tick();
    //buttons[1].tick();
    //buttons[2].tick();
    //tft->drawString("Hello Tymer!", 20, 20);c++ instanceof
    //this->menu.draw();
    //this->menu.nextItem();
    //this->modules[CLOCK]->draw(tft);

    //run_module();
    //if (buttons[2].event() == BTN_LONG && activeModule != NULL) {
    //    activeModule = NULL;
    //    menu.setIndex(0);
    //    menu.draw();
    //    inMenu = true;
    //    Serial.println("back!");
    //}
    //if (inMenu && buttons[0].event() == BTN_SINGLE) {
    //    menu.nextItem();
    //    menu.draw();
    //    Serial.println("down!");
    //} else if (inMenu && buttons[1].event() == BTN_SINGLE) {
    //    menu.prevItem();
    //    menu.draw();
    //    Serial.println("up!");
    //}
    //if (inMenu && activeModule == NULL && buttons[2].event() == BTN_SINGLE) {
    //    inMenu = false;
    //    activeModule = modules[menu.getSelected()->getApp()];
    //    Serial.println(activeModule->getName());
    //    gfx->fillScreen(BLACK);
    //    delay(20);
    //}
    //for(int i = 0; i < 3; i++) {
    //    buttons[i].tick();
    //    button_events[i] = buttons[i].event();
    //}
    //delay(1000);

    menu.draw();
    draw_topbar();
    delay(1000);
}
