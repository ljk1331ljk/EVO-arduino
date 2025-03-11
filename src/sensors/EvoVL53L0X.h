/**
 * @file EvoVL53L0X.h
 * @brief Class for interfacing with the VL53L0X Time-of-Flight distance sensor using the EvoI2CDevice library.
 */
#ifndef EVO_VL53L0X_H
#define EVO_VL53L0X_H

#include "../helper/EvoI2CDevice.h"
#include <Adafruit_VL53L0X.h>

/**
 * @class EvoVL53L0X
 * @brief Class to interact with the VL53L0X Time-of-Flight (ToF) distance sensor.
 */
class EvoVL53L0X
{
private:
    Adafruit_VL53L0X lox;                            /**< Instance of the Adafruit VL53L0X driver */
    I2CChannel _channel;                             /**< I2C channel used for communication */
    VL53L0X_RangingMeasurementData_t measure;        /**< Struct to store distance measurement data */
    I2CDevice &i2CDevice = I2CDevice::getInstance(); /**< Reference to the singleton I2CDevice instance */

public:
    /**
     * @brief Constructs an EvoVL53L0X object.
     * @param channel The I2C channel to use.
     */
    EvoVL53L0X(I2CChannel channel);

    /**
     * @brief Initializes the VL53L0X sensor.
     */
    void begin(bool continuous = false);

    /**
     * @brief Retrieves the distance measured by the sensor.
     * @return Distance in millimeters. Returns 2000 when there is an error or when maximum reading range is reached.
     */
    int getDistance();

    /**
     * @brief Retrieves the distance measured by the sensor in continuous mode.
     * @return Distance in millimeters. Returns 2000 when there is an error or when maximum reading range is reached.
     */
    int getDistanceContinuous();
};
#endif