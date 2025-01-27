#include "EvoTCS34725.h"

void EvoTCS34725::begin()
{

    i2CDevice.selectChannel(_channel);
    if (!this->tcs.begin())
    {
        Serial.println(F("Failed to boot VL53L0X"));
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
