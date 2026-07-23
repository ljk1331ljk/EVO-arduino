#ifndef EVO_BOARD_DEFINITION_H
#define EVO_BOARD_DEFINITION_H

#include <Arduino.h>

enum class EvoBoardId : uint8_t
{
    X1E,
    X1P
};

struct EvoMotorPortPins
{
    uint8_t power1;
    uint8_t power2;
    uint8_t tach1;
    uint8_t tach2;
};

#endif
