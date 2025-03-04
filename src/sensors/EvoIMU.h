#ifndef _EVO_IMU_H_
#define _EVO_IMU_H_

/**
 * @file EvoIMU.h
 * @brief Class for interfacing with the MPU9250 IMU sensor using the EvoI2CDevice library.
 */

#include "../helper/EvoI2CDevice.h"
#include <MPU9250.h>

/**
 * @class EvoIMU
 * @brief Class to interact with the MPU9250 IMU sensor.
 */
class EvoIMU {
public:
    /**
     * @brief Constructs an EvoIMU object.
     * @param channel The I2C channel to use for communication.
     */
    EvoIMU(I2CChannel channel)
    {
        _channel = channel;
    }

    /**
     * @brief Initializes the sensor and checks communication.
     * @return True if initialization is successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Reads all sensor data from the IMU.
     */
    void readSensors();

    /**
     * @brief Gets the temperature from the sensor.
     * @return The temperature in degrees Celsius.
     */
    float getTemperature();

    /**
     * @brief Gets magnetometer data.
     * @param magData Pointer to store the magnetometer data (x, y, z).
     */
    void readMagnetometer(int16_t *magData);

    /**
     * @brief Gets accelerometer data.
     * @param ax Pointer to store the x-axis acceleration.
     * @param ay Pointer to store the y-axis acceleration.
     * @param az Pointer to store the z-axis acceleration.
     */
    void readAccelerometer(int16_t *ax, int16_t *ay, int16_t *az);

    /**
     * @brief Gets gyroscope data.
     * @param gx Pointer to store the x-axis gyroscope data.
     * @param gy Pointer to store the y-axis gyroscope data.
     * @param gz Pointer to store the z-axis gyroscope data.
     */
    void readGyroscope(int16_t *gx, int16_t *gy, int16_t *gz);

    /**
     * @brief New method for reading pressure data.
     * @return The pressure value.
     */
    float readPressure();

private:
    MPU9250 mpu; /**< Instance of the MPU9250 driver */
    float temperature; /**< Store temperature value */
    I2CChannel _channel; /**< I2C channel used for communication */
};

#endif // _EVO_IMU_H_
