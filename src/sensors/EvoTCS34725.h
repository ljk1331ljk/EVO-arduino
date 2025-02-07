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
    uint8_t _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_2_4MS;
    tcs34725Gain_t _tcs34725Gain = TCS34725_GAIN_16X;

public:
    // Constructor with port and positive direction
    EvoTCS34725(I2CChannel channel) : tcs(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X)
    {
        _channel = channel;
    }
    void begin();

    void setIntegrationTime(uint8_t it);
    void setGain(tcs34725Gain_t gain);

    void getRGB(float *r, float *g, float *b);
    void getRawRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
    uint16_t getRawRed();
    uint16_t getRawGreen();
    uint16_t getRawBlue();
    uint16_t getRawClear();
    float getRed();
    float getGreen();
    float getBlue();
};
#endif