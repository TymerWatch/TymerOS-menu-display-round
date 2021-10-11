#include "../module.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>


Module::Module() {

}

Module::Module(char *name) {
    this->name = name;
}

/**
 * Returns name of the module
 * @return name - string
 */
String Module::getName() {
    return name;
}

/**
 * Set name of module
 * @param name of module
 */
void Module::setName(char *name) {
    this->name = name;
}
