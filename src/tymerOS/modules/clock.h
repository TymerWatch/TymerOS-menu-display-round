#ifndef _CLOCK_H
#define _CLOCK_H

#include "../module.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "Fonts/FreeMono12pt7b.h"
#include "Fonts/FreeMonoBold12pt7b.h"

typedef struct _clock_time_t {
    uint8_t hour;
    uint8_t minute;
    uint8_t second; 
} clock_time_t;

typedef struct _clock_date_t {
    uint8_t day;
    uint8_t month;
    uint16_t year;
    String weekday;
} clock_date_t;

typedef enum _clock_face_t {
    CLOCK_FACE_SIMPLE,
    CLOCK_FACE_INFO,
    CLOCK_FACE_TERMINAL
} clock_face_t;


class Clock : public Module {
private:
    clock_date_t date;
    clock_time_t time;
    clock_face_t face;
public:
    // TODO: add RTC chip initializer
    Clock();
    virtual void draw(Arduino_GFX *gfx) {
        int16_t x,y;
        clock_time_t *time = getTime();
        String out = String(time->hour) + "-" + String(time->minute);
        gfx->setFont(&FreeMonoBold12pt7b);
        gfx->setTextSize(2);
        uint16_t width,height;
        gfx->getTextBounds(out, 0,0,&x,&y,&width,&height);
        gfx->setCursor(120-(width/2), 120-(height/2));
        gfx->print(out);
        gfx->setFont(&FreeMono12pt7b);
        gfx->setTextSize(1);
    }
    void receiveButtons(int *state); 
    clock_time_t *getTime();
    clock_date_t *getDate();
    clock_face_t getFace();
    void setTime(uint8_t hour, uint8_t minute);
    void setDate(uint8_t day, uint8_t month, uint16_t year, char* weekday);
    void setFace(clock_face_t face);
};
#endif