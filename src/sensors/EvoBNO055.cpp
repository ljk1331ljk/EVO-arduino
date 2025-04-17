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

void EvoBNO055::resetHeading()
{
    _referenceHeading = this->getEulerX();
    _rotationCount = 0;
}

float EvoBNO055::getRelativeHeading()
{
    float heading = (this->getEulerX() - _referenceHeading);
    float relativeHeading = fmod((heading + 180.0), 360.0) - 180.0;
    if (relativeHeading <= -180.0)
    {
        relativeHeading += 360.0;
    }
    Serial.print(relativeHeading);
    Serial.print(" ");
    float delta = relativeHeading - _lastRelativeHeading;
    Serial.print(delta);
    Serial.print(" ");
    if (delta >= 180.0)
    {
        _rotationCount--;
    }
    else if (delta <= -180.0)
    {
        _rotationCount++;
    }
    _lastRelativeHeading = relativeHeading;
    float continuousHeading = relativeHeading + (_rotationCount * 360.0);
    Serial.print(_rotationCount);
    Serial.print(" ");
    Serial.println(continuousHeading);
    return continuousHeading;
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
