#include "EvoTCS34725.h"

void EvoTCS34725::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!this->tcs.begin())
    {
        Serial.println(F("Failed to boot TCS34725"));
    }
}

void EvoTCS34725::getRGB(float *r, float *g, float *b)
{
    i2CDevice.selectChannel(_channel);
    tcs.getRGB(r, g, b);
}
void EvoTCS34725::getRawRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
    i2CDevice.selectChannel(_channel);
    tcs.getRawData(r, g, b, c);
}

void EvoTCS34725::setIntegrationTime(uint8_t it)
{
    i2CDevice.selectChannel(_channel);
    _tcs34725IntegrationTime = it;
    tcs.setIntegrationTime(_tcs34725IntegrationTime);
}
void EvoTCS34725::setGain(tcs34725Gain_t gain)
{
    i2CDevice.selectChannel(_channel);
    _tcs34725Gain = gain;
    tcs.setGain(_tcs34725Gain);
}
uint16_t EvoTCS34725::getRawRed()
{
    i2CDevice.selectChannel(_channel);
    uint16_t red = tcs.read16(TCS34725_RDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return red;
}
uint16_t EvoTCS34725::getRawGreen()
{
    i2CDevice.selectChannel(_channel);
    uint16_t green = tcs.read16(TCS34725_GDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return green;
}
uint16_t EvoTCS34725::getRawBlue()
{
    i2CDevice.selectChannel(_channel);
    uint16_t blue = tcs.read16(TCS34725_BDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return blue;
}
uint16_t EvoTCS34725::getRawClear()
{
    i2CDevice.selectChannel(_channel);
    uint16_t clear = tcs.read16(TCS34725_CDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return clear;
}

float EvoTCS34725::getRed()
{
    i2CDevice.selectChannel(_channel);
    uint16_t red = tcs.read16(TCS34725_RDATAL);
    uint32_t clear = tcs.read16(TCS34725_CDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    if (clear == 0)
    {
        return 0;
    }
    else
    {
        return (float)red / clear * 255.0;
    }
}
float EvoTCS34725::getGreen()
{
    i2CDevice.selectChannel(_channel);
    uint16_t green = tcs.read16(TCS34725_GDATAL);
    uint32_t clear = tcs.read16(TCS34725_CDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    if (clear == 0)
    {
        return 0;
    }
    else
    {
        return (float)green / clear * 255.0;
    }
}
float EvoTCS34725::getBlue()
{
    i2CDevice.selectChannel(_channel);
    uint16_t blue = tcs.read16(TCS34725_BDATAL);
    uint32_t clear = tcs.read16(TCS34725_CDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    if (clear == 0)
    {
        return 0;
    }
    else
    {
        return (float)blue / clear * 255.0;
    }
}