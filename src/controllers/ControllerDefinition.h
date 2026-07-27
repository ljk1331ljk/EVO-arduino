#ifndef EVO_CONTROLLER_DEFINITION_H
#define EVO_CONTROLLER_DEFINITION_H
#include <Arduino.h>
using EvoControllerId = uint8_t;

enum ButtonState
{
    PRESSED,
    RELEASED
};

enum I2CChannel
{
    I2CUNDEFINED = -1,
    I2C1 = 0,
    I2C2 = 1,
    I2C3 = 2,
    I2C4 = 3,
    I2C5 = 4,
    I2C6 = 5,
    I2C7 = 6,
    I2C8 = 7
};

#endif
