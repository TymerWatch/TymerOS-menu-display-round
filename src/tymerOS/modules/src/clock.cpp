#include "../clock.h"
#include "../../module.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>

Clock::Clock() : Module("Clock") {

}


void Clock::receiveButtons(int *state) {
    uint8_t state_select =  state[BUTTON_SELECT];
    uint8_t state_up     =  state[BUTTON_UP];
    uint8_t state_down   =  state[BUTTON_DOWN];
    uint8_t state_fn     =  state[BUTTON_FN];
}

clock_time_t *Clock::getTime() {
    return &this->time;
}

clock_date_t *Clock::getDate() {
    return &this->date;
}

void Clock::setDate(uint8_t day, uint8_t month, uint16_t year, char *weekday) {
    this->date.day = day;
    this->date.month = month;
    this->date.year = year;
    this->date.weekday = weekday;
}

void Clock::setTime(uint8_t hour, uint8_t minute) {
    this->time.hour = hour;
    this->time.minute = minute;
    this->time.second = 0;
}