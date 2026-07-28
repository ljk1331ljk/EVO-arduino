/**
 * @file EvoIMU.h
 * @brief Class for interfacing with the TCS34725 color sensor using the EvoI2CDevice library.
 */
#ifndef EVO_IMU_H
#define EVO_IMU_H

#include "../helper/EvoI2CDevice.h"
#include "../helper/AdafruitSensors/Adafruit_BNO055.h"

/**
 * @class EvoIMU
 * @brief Class to interact with the BNO055 Inertial Measurement Unit (IMU) sensor.
 */
class EvoIMU
{
private:
#if defined(EVO_BOARD_X1E)
    static constexpr uint8_t IMU_ADDRESS = BNO055_ADDRESS_B; // 0x29
#elif defined(EVO_BOARD_X1P)
    static constexpr uint8_t IMU_ADDRESS = BNO055_ADDRESS_A; // 0x28
#else
#error "No EVO controller selected. Define EVO_BOARD_X1E or EVO_BOARD_X1P."
#endif

    Adafruit_BNO055 bno;                             /**< Instance of the Adafruit BNO055 driver */
    I2CChannel _channel;                             /**< I2C channel used for communication */
    I2CDevice &i2CDevice = I2CDevice::getInstance(); /**< Reference to the singleton I2CDevice instance */
    sensors_event_t event;                           /**< Event structure to hold sensor data */
    float _referenceHeading = 0;                     /**< Reference heading for the sensor */
    float _lastRelativeHeading = 0;
    int _rotationCount = 0;

public:
    /**
     * @brief Constructs an EvoTCS34725 object.
     * @param channel The I2C channel to use.
     */
    EvoIMU(I2CChannel channel) : bno(55, IMU_ADDRESS)
    {
        _channel = channel;
    }

    /**
     * @brief Initializes the BNO055 sensor.
     */
    bool begin();

    /**
     * @brief Sets the reference heading for the sensor.
     */
    void resetHeading();

    /**
     * @brief Get the Relative Heading object.
     * @return Relative heading in degrees.
     * @details The relative heading is the difference between the current heading and the reference heading.
     */
    float getRelativeHeading();

    /**
     * @brief Gets the Euler angles of the sensor.
     * @param x Pointer to store the X angle.
     * @param y Pointer to store the Y angle.
     * @param z Pointer to store the Z angle.
     */
    void getEuler(float *x, float *y, float *z);

    /**
     * @brief Gets the euler angle in the x direction of the sensor.
     * @return Angle in degrees.
     */
    float getEulerX();

    /**
     * @brief Gets the euler angle in the y direction of the sensor.
     * @return Angle in degrees.
     */
    float getEulerY();

    /**
     * @brief Gets the euler angle in the z direction of the sensor.
     * @return Angle in degrees.
     */
    float getEulerZ();
};
#endif
