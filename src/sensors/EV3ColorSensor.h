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

/**
 * @class EV3ColorSensor
 * @brief Class to interact with the EV3 Color Sensor.
 */
class EV3ColorSensor
{
public:
    /**
     * @brief Constructs an EV3ColorSensor object.
     * @param port The sensor port the color sensor is connected to.
     */
    EV3ColorSensor(SensorPort port);

    /**
     * @brief Initializes the EV3 Color Sensor.
     * @return True if the EV3 Color Sensor was successfully initialized, false otherwise.
     */
    bool begin();

    /**
     * @brief Sets the operating mode of the EV3 Color Sensor.
     * @param mode The operating mode to set
     * COL_CAL
     * RGB_RAW
     * REF_RAW
     * COL_COLOR
     * COL_AMBIENT
     * COL_REFLECT
     */
    void setMode(EV3ColorSensorMode mode);

    /**
     * @brief Retrieves the reflected light sensor value.
     * @return reflected light sensor value.
     */
    int getReflection();

    /**
     * @brief Retrieves the ambient light sensor value.
     * @return ambient light sensor value.
     */
    int getAmbient();

    /**
     * @brief Retrieves the detected color.
     * @return detected color as EV3ColorSensorColor enum.
     * NONE = 0
     * COLOR_BLACK = 1
     * COLOR_BLUE = 2
     * COLOR_GREEN = 3
     * COLOR_YELLOW = 4
     * COLOR_RED = 5
     * COLOR_WHITE = 6
     *COLOR_BROWN = 7
     */
    int getColor();

private:
    SensorPort _port;
    EvoSensorPort _EV3port;
    EV3ColorSensorMode _mode;

    int value;
    void messageHandler(uint8_t mode, uint8_t *message, int length);
};
#endif