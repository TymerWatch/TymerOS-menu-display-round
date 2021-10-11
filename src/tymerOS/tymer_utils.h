#ifndef _TYMER_UTILS_H
#define _TYMER_UTILS_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>


void rotate_point(int x, int y, float angle, int sx, int sy, int *x2, int *y2) {
    float radians = angle * PI / 180;
    *x2 = (x - sx) * cos(radians) - (y - sy) * sin(radians) + sx;
    *y2 = (x - sx) * sin(radians) + (y - sy) * cos(radians) + sy;
};
#endif