#ifndef EVO_VL53L0X_H
#define EVO_VL53L0X_H

#include "../helper/EvoI2CDevice.h"
#include <Adafruit_VL53L0X.h>

class EvoVL53L0X
{
private:
    Adafruit_VL53L0X lox;
    I2CChannel _channel;
    VL53L0X_RangingMeasurementData_t measure;
    I2CDevice &i2CDevice = I2CDevice::getInstance();

public:
    // Constructor with port and positive direction
    EvoVL53L0X(I2CChannel channel);
    void begin();
    int getDistance();
};
#endif