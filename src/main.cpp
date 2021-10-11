#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <SPI.h>
//#include <Fonts/FreeMono9pt7b.h>
#include "Fonts/FreeMonoBold9pt7b.h"
#include "pindef.h"
#include "tymerOS/menu.h"
#include "tymerOS/tymer.h"

//Arduino_DataBus *bus = new Arduino_HWSPI(27, 5);
//Arduino_GFX *gfx = create_default_Arduino_GFX();
//Arduino_DataBus *bus = create_default_Arduino_DataBus(); 
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(DP_DC, DP_CS, DP_CLK, DP_MOSI, DP_MISO);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 33, 0);
Arduino_Canvas *canvas = new Arduino_Canvas(100,100, gfx, 0,0);

#define DP_HEIGHT   (240)
#define DP_WIDTH    (240)
#define TOPBAR_HEIGHT   (20)
#define DP_ORIGIN   0,0


#define GFX_WHITE BLACK
#define GFX_BLACK WHITE

void rotate_point(int x, int y, float angle, int sx, int sy, int index);
void draw_overlay();
void clock_widget();
void setup_menu();


char *wifi_ssid = "FRITZ!Box 7580 ME";
char *wifi_pwd = "9546792276287867";
Tymer tymer;


void setup() {
    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->setCursor(100, 100);
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2);
    gfx->println("Hello World!");
    gfx->invertDisplay(true);
    gfx->setRotation(2);
    Serial.begin(115200);
    tymer = Tymer(gfx, wifi_ssid, wifi_pwd);
    //setCpuFrequencyMhz(240);
}

void loop() {
    ////canvas->fillScreen(WHITE);
    //gfx->fillScreen(BLACK);
    ////gfx->fillRect(0,0,40,100,WHITE);

    //int x = 220, y = 120;

    //float angle = -40;
    //for (int i = 0; i < 5; i++) {
    //    rotate_point(x, y, angle, 120, 120, i);
    //    angle += 20;
    //}
    //draw_overlay();
    //delay(1000);
    tymer.loop();
}

void rotate_point(int x, int y, float angle, int sx, int sy, int index) {
    float radians = angle * PI / 180;
    int x2 = (x - sx) * cos(radians) - (y - sy) * sin(radians) + sx;
    int y2 = (x - sx) * sin(radians) + (y - sy) * cos(radians) + sy;
    if (index == 2) {
        gfx->fillCircle(x2,y2, 4, ORANGE);
    } else {
        gfx->fillCircle(x2, y2, 1, ORANGE);
    }
    gfx->setCursor(x2-70, y2);
    gfx->setTextSize(1);
    gfx->setFont(NULL);
    gfx->setTextColor(WHITE);
    gfx->printf("Element %d", index);
}

void draw_overlay() {
    int16_t x1,y1;
    uint16_t w,h;
    //gfx->drawFastHLine(0, 30, 240, WHITE);
    gfx->fillRect(DP_ORIGIN, DP_WIDTH, TOPBAR_HEIGHT, WHITE);
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

void clock_widget() {
}
