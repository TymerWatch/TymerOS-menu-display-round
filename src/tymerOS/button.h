#ifndef _BUTTON_H
#define _BUTTON_H

#include <Arduino.h>

class Btn;

enum btn_state {
    BTN_NO_PRESS,
    BTN_SINGLE,
    BTN_DOUBLE,
    BTN_LONG
};

class Btn {
public:
    Btn();
    Btn(uint8_t pin);
    uint8_t event();
    void tick();
    void setDebounceMs(uint16_t ms);
    void setClickTimeoutMs(uint16_t ms);
private:
    // cur read value of pin
    bool cur_read;
    // prev read value of pin
    bool prev_read;
    uint8_t pin;
    // current state of pin
    uint8_t state;
    // previous state of pin
    uint8_t prev_state;
    // debounce time for switch close
    uint16_t debounce;
    // max time between two clicks
    uint16_t click_timeout;
    // down time of button
    uint16_t down_time;
    // up time of button
    uint16_t up_time;
    // hold time
    uint16_t hold_time;
    // single waiting
    bool singleOk;
    bool dc_on_up;
    bool dc_waiting;
};

#endif