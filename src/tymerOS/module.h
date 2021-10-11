#ifndef _MODULE_H
#define _MODULE_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#define BUTTON_SELECT   0
#define BUTTON_UP       1
#define BUTTON_DOWN     2
#define BUTTON_FN       3

class Module;

class Module {
public:
    Module();
    Module(char *name);
    void receiveButtons(int *state);
    virtual void draw(Arduino_GFX *gfx) {
        gfx->setCursor(50, 50);
        gfx->print(getName());
    }
    String getName();
    void setName(char *name);
private:
    String name;
};
#endif /* _MODULE_H */