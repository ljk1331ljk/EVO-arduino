#include "EvoBNO055.h"

bool EvoBNO055::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!this->bno.begin())
    {
        Serial.println(F("Failed to boot BNO055"));
        return false;
    }
    return true;
}

void EvoBNO055::getEuler(float *x, float *y, float *z)
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    *x = event.orientation.x;
    *y = event.orientation.y;
    *z = event.orientation.z;
}

float EvoBNO055::getEulerX()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.x;
}

float EvoBNO055::getEulerY()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.y;
}

float EvoBNO055::getEulerZ()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.z;
}
