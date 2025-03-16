#include "EvoIMU.h"

EvoIMU::EvoIMU(I2CChannel channel) : _channel(channel), imu(MPU9250_ADDRESS_AD0_LOW) {}

void EvoIMU::begin()
{
    i2CDevice.selectChannel(_channel);
    Wire.begin();
    imu.setWire(&Wire);

    uint8_t id;
    if (imu.readId(&id) != 0) {
        Serial.println(F("Failed to read IMU ID"));
    }

    // Initialize accelerometer
    imu.beginAccel(ACC_FULL_SCALE_16_G);

    // Initialize gyroscope
    imu.beginGyro(GYRO_FULL_SCALE_2000_DPS);

    // Initialize magnetometer
    imu.beginMag(MAG_MODE_CONTINUOUS_8HZ);

    Serial.println(F("IMU initialized"));
}

void EvoIMU::getAccelerometer(float *ax, float *ay, float *az, float *aSqrt)
{
    i2CDevice.selectChannel(_channel);

    if (imu.accelUpdate() == 0) {
        *ax = imu.accelX();
        *ay = imu.accelY();
        *az = imu.accelZ();
        *aSqrt = imu.accelSqrt();
    } else {
        Serial.println("Cannot read accelerometer values");
    }
}

void EvoIMU::getGyroscope(float *gx, float *gy, float *gz)
{
    i2CDevice.selectChannel(_channel);

    if (imu.gyroUpdate() == 0) {
        *gx = imu.gyroX();
        *gy = imu.gyroY();
        *gz = imu.gyroZ();
    } else {
        Serial.println("Cannot read gyroscope values");
    }
}

void EvoIMU::getMagnetometer(float *mx, float *my, float *mz, float *mDirection)
{
    i2CDevice.selectChannel(_channel);

    if (imu.magUpdate() == 0) {
        *mx = imu.magX();
        *my = imu.magY();
        *mz = imu.magZ();
        *mDirection = imu.magHorizDirection();
    } else {
        Serial.println("Cannot read magnetometer values");
    }
}  