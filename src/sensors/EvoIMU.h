/**
 * @file EvoIMU.h
 * @brief Class for interfacing with the GY-91 IMU sensor.
 */
#ifndef EVO_IMU_H
#define EVO_IMU_H

#include "../helper/EvoI2CDevice.h"
#include "MPU9250_asukiaaa.h"

/**
 * @class EvoIMU
 * @brief Class to interact with the GY-91 IMU sensor.
 */
class EvoIMU
{
private:
    MPU9250_asukiaaa imu; // Using MPU9250_asukiaaa library
    I2CChannel _channel;                          
    I2CDevice &i2CDevice = I2CDevice::getInstance(); 

public:
    /**
     * @brief Constructs an EvoIMU object.
     * @param channel The I2C channel to use.
     */
    EvoIMU(I2CChannel channel);

    /**
     * @brief Initializes the EvoIMU sensor.
     */
    void begin();

    /**
     * @brief Retrieves the accelerometer readings.
     * @param ax Pointer to store the x-axis value.
     * @param ay Pointer to store the y-axis value.
     * @param az Pointer to store the z-axis value.
     */
    void getAccelerometer(float *ax, float *ay, float *az, float *aSqrt);

    /**
     * @brief Retrieves the gyroscope readings.
     * @param gx Pointer to store the x-axis value.
     * @param gy Pointer to store the y-axis value.
     * @param gz Pointer to store the z-axis value.
     */
    void getGyroscope(float *gx, float *gy, float *gz);

    /**
     * @brief Retrieves the magnetometer readings.
     * @param mx Pointer to store the x-axis value.
     * @param my Pointer to store the y-axis value.
     * @param mz Pointer to store the z-axis value.  
     */
    void getMagnetometer(float *mx, float *my, float *mz, float *mDirection);
};

#endif