#include "EvoRGBColorSensor.h"

bool EvoRGBColorSensor::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!this->tcs.begin())
    {
        return false;
    }
    return true;
}

void EvoRGBColorSensor::getRGB(float *r, float *g, float *b)
{
    i2CDevice.selectChannel(_channel);
    tcs.getRGB(r, g, b);
}
void EvoRGBColorSensor::getRawRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
    i2CDevice.selectChannel(_channel);
    tcs.getRawData(r, g, b, c);
}

void EvoRGBColorSensor::getHSV(float *h, float *s, float *v)
{
    float r, g, b;
    getRGB(&r, &g, &b);

    // Normalize RGB values to 0-1s
    float rNorm = r / 1024.0f;
    float gNorm = g / 1024.0f;
    float bNorm = b / 1024.0f;

    // Find minimum and maximum values among R, G, B
    float minVal = min(rNorm, min(gNorm, bNorm));
    float maxVal = max(rNorm, max(gNorm, bNorm));
    float delta = maxVal - minVal;

    // Calculate Value
    *v = maxVal * 100;

    // Calculate Saturation
    if (maxVal != 0)
        *s = (delta / maxVal) * 100;
    else
    {
        *s = 0;
        *h = -1;
        return;
    }

    // Calculate Hue
    if (delta == 0)
        *h = 0;
    else if (maxVal == rNorm)
        *h = 60 * (fmod(((gNorm - bNorm) / delta), 6));
    else if (maxVal == gNorm)
        *h = 60 * (((bNorm - rNorm) / delta) + 2);
    else if (maxVal == bNorm)
        *h = 60 * (((rNorm - gNorm) / delta) + 4);

    if (*h < 0)
        *h += 360;
}

void EvoRGBColorSensor::setIntegrationTime(uint8_t it)
{
    i2CDevice.selectChannel(_channel);
    _tcs34725IntegrationTime = it;
    tcs.setIntegrationTime(_tcs34725IntegrationTime);
}
void EvoRGBColorSensor::setGain(tcs34725Gain_t gain)
{
    i2CDevice.selectChannel(_channel);
    _tcs34725Gain = gain;
    tcs.setGain(_tcs34725Gain);
}
uint16_t EvoRGBColorSensor::getRawRed()
{
    i2CDevice.selectChannel(_channel);
    uint16_t red = tcs.read16(TCS34725_RDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return red;
}
uint16_t EvoRGBColorSensor::getRawGreen()
{
    i2CDevice.selectChannel(_channel);
    uint16_t green = tcs.read16(TCS34725_GDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return green;
}
uint16_t EvoRGBColorSensor::getRawBlue()
{
    i2CDevice.selectChannel(_channel);
    uint16_t blue = tcs.read16(TCS34725_BDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return blue;
}
uint16_t EvoRGBColorSensor::getRawClear()
{
    i2CDevice.selectChannel(_channel);
    uint16_t clear = tcs.read16(TCS34725_CDATAL);
    delay((256 - _tcs34725IntegrationTime) * 12 / 5 + 1);
    return clear;
}

float EvoRGBColorSensor::getRed()
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
float EvoRGBColorSensor::getGreen()
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
float EvoRGBColorSensor::getBlue()
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