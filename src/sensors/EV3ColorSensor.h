#ifndef EV3_COLOR_SENSOR_H
#define EV3_COLOR_SENSOR_H

#include "../helper/EvoSensorPort.h"

enum struct EV3ColorSensorColor : uint8_t
{
    NONE = 0,
    COLOR_BLACK = 1,
    COLOR_BLUE = 2,
    COLOR_GREEN = 3,
    COLOR_YELLOW = 4,
    COLOR_RED = 5,
    COLOR_WHITE = 6,
    COLOR_BROWN = 7
};

const char *toColor(int col);

enum struct EV3ColorSensorMode : uint8_t
{
    COL_CAL = 5,
    RGB_RAW = 4,
    REF_RAW = 3,
    COL_COLOR = 2,
    COL_AMBIENT = 1,
    COL_REFLECT = 0
};

class EV3ColorSensor
{
public:
    SensorPort _port;
    EV3ColorSensor(SensorPort port);
    bool begin();
    void setMode(EV3ColorSensorMode mode);
    int getReflection();
    int getAmbient();
    int getColor();

private:
    EvoSensorPort _EV3port;
    EV3ColorSensorMode _mode;

    int value;
    void messageHandler(uint8_t mode, uint8_t *message, int length);
};
#endif