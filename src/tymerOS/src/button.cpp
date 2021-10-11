#include <Arduino.h>
#include "../button.h"

Btn::Btn() {

}

Btn::Btn(uint8_t pin) {
    this->pin = pin;
    this->state = BTN_NO_PRESS;
    this->cur_read = false;
    this->prev_read = false;
    this->debounce = 20;
    this->click_timeout = 150;
    this->down_time = -1;
    this->up_time = -1;
    this->hold_time = 1500;
    pinMode(pin, INPUT);
}

/**
 * Returns current event state of the button
 * BTN_NO_PRESS, BTN_SINGLE, BTN_DOUBLE, BTN_LONG
 * @return event state of button
 */
uint8_t Btn::event() {
    return this->state;
}

/**
 * Debounces and fetches event state of button and sets it
 */
void Btn::tick() {
    cur_read = digitalRead(this->pin);
    //uint8_t out_event = BTN_NO_PRESS;
    this->state = BTN_NO_PRESS;

    if (cur_read == HIGH && prev_read == LOW && (millis() - up_time) > debounce) {
        down_time = millis();
        //singleOk = true;
    } else if (cur_read == LOW && prev_read == HIGH && (millis() - down_time) > debounce) {
        up_time = millis();
        if ((millis() - down_time) < hold_time) {
            this->state = BTN_SINGLE;
        }
        //out_event = BTN_DOUBLE;
    }
    if (cur_read == HIGH && (millis() - down_time) >= hold_time) {
        this->state = BTN_LONG;
    }
    prev_read = cur_read;
    //this->state = out_event;
}

/**
 * Sets the debounce time for the switch in ms
 * @param ms time in ms
 */
void Btn::setDebounceMs(uint16_t ms) {
    this->debounce = ms;
}

/**
 * Sets the max time between two clicks
 * @param ms time in ms
 */
void Btn::setClickTimeoutMs(uint16_t ms) {
    this->click_timeout = ms;
}