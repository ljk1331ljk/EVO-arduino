#ifndef EVO_TCS34725_H
#define EVO_TCS34725_H

#include "../helper/EvoI2CDevice.h"
#include <Adafruit_TCS34725.h>

class EvoTCS34725
{
private:
    Adafruit_TCS34725 tcs;
    I2CChannel _channel;
    I2CDevice &i2CDevice = I2CDevice::getInstance();

public:
    // Constructor with port and positive direction
    EvoTCS34725(I2CChannel channel) : tcs(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X)
    {
        _channel = channel;
    }
    void begin();
    void getRGB(float *r, float *g, float *b);
    void getRawRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
};
#endif