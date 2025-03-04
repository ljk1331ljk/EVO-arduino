#include "EvoIMU.h"

EvoIMU::EvoIMU(I2CChannel channel)
{
    _channel = channel;
}

bool EvoIMU::begin() 
{
    I2CDevice::getInstance().selectChannel(_channel); // Correctly reference the singleton instance
    if (!this->mpu.begin())
    {
        Serial.println(F("Failed to boot IMU"));
        return false; // Return false if initialization fails
    }
    return true; // Return true if initialization is successful
}

void EvoIMU::readSensors() {
    // Read accelerometer, gyroscope, and magnetometer data
    int16_t accelData[3], gyroData[3], magData[3];
    mpu.readAccelData(accelData);
    mpu.readGyroData(gyroData);
    mpu.readMagData(magData);
    temperature = mpu.readTempData(); // Assuming temperature is read from MPU9250
}

float EvoIMU::getTemperature() {
    return temperature; // Return the temperature value
}

void EvoIMU::readMagnetometer(int16_t *magData) {
    mpu.readMagData(magData); // Read magnetometer data
}

void EvoIMU::readAccelerometer(int16_t *ax, int16_t *ay, int16_t *az) {
    int16_t accelData[3];
    mpu.readAccelData(accelData); // Read accelerometer data
    *ax = accelData[0];
    *ay = accelData[1];
    *az = accelData[2];
}

void EvoIMU::readGyroscope(int16_t *gx, int16_t *gy, int16_t *gz) {
    int16_t gyroData[3];
    mpu.readGyroData(gyroData); // Read gyroscope data
    *gx = gyroData[0];
    *gy = gyroData[1];
    *gz = gyroData[2];
}

float EvoIMU::readPressure() {
    // Placeholder for pressure reading logic
    return 0.0; // Replace with actual pressure reading
}
