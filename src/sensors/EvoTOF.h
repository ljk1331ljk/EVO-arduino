/**
 * @file EvoTOF.h
 * @brief Class for interfacing with the VL53L0X Time-of-Flight distance sensor using the EvoI2CDevice library.
 */
#ifndef EVO_TOF_H
#define EVO_TOF_H

#include "../helper/EvoI2CDevice.h"
#include "../helper/VL53L0X.h"

/**
 * @class EvoTOF
 * @brief Class to interact with the VL53L0X Time-of-Flight (ToF) distance sensor.
 */
class EvoTOF
{
private:
    I2CChannel _channel;                             /**< I2C channel used for communication */
    VL53L0X lox;                                     /**< Instance of the VL53L0X driver */
    I2CDevice &i2CDevice = I2CDevice::getInstance(); /**< Reference to the singleton I2CDevice instance */

public:
    /**
     * @brief Constructs an EvoTOF object.
     * @param channel The I2C channel to use.
     */
    EvoTOF(I2CChannel channel);

    /**
     * @brief Initializes the VL53L0X sensor.
     * @param continuous Sets the sensor in continuous or non-continuous mode
     * if true, the sensor will continuously measure distance at a specified interval.
     * @return True if the sensor was successfully initialized, false otherwise.
     */
    bool begin(bool continuous = false);

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

    /**
     * @brief Configures the sensor for long-range measurements.
     * @param enable If true, configures the sensor for long-range mode; otherwise, sets it to default mode.
     */
    void setLongRange(bool enable);

    /**
     * @brief Sets the sensor to high accuracy mode.
     */
    void setHighAccuracyMode();

    /**
     * @brief Sets the sensor to high speed mode.
     */
    void setHighSpeedMode();
};
#endif