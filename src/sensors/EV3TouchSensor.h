/** \file EV3TouchSensor.h
 *  \brief Class for interfacing with the EV3 Touch Sensor.
 */
#ifndef EVO_EV3TOUCHSENSOR_H
#define EVO_EV3TOUCHSENSOR_H
#include <Arduino.h>
#include "../helper/EvoSensorPort.h"

/**
 * @class EV3TouchSensor
 * @brief Class to interact with the EV3 Touch Sensor.
 */
class EV3TouchSensor
{
private:
    SensorPort _port; /**< The sensor port the touch sensor is connected to */
    int _pin;         /**< The pin number for reading the touch sensor state */
public:
    /**
     * @brief Constructs an EV3TouchSensor object.
     * @param port The sensor port the touch sensor is connected to.
     */
    EV3TouchSensor(SensorPort port);

    /**
     * @brief Gets the state of the button.
     * @return The state of the button. (0 = RELEASED, 1 = PRESSED).
     */
    int getButton();

    /**
     * @brief Waits for the button pressed before continuing execution.
     * @param debouncems Delay in milliseconds after button is pressed.
     */
    void waitForPress(int debouncems = 200);

    /**
     * @brief Waits for the button released before continuing execution.
     * @param debouncems Delay in milliseconds after button is released.
     */
    void waitForRelease(int debouncems = 200);

    /**
     * @brief Waits for the button pressed and released before continuing execution.
     * @param debouncems Delay in milliseconds after button is pressed and released.
     */
    void waitForBump(int debouncems = 200);
};

#endif
