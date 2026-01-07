#include "EvoIMU.h"

bool EvoIMU::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!this->bno.begin())
    {
        return false;
    }
    return true;
}

void EvoIMU::resetHeading()
{
    _referenceHeading = this->getEulerX();
    _rotationCount = 0;
}

float EvoIMU::getRelativeHeading()
{
    float heading = (this->getEulerX() - _referenceHeading);
    float relativeHeading = fmod((heading + 180.0), 360.0) - 180.0;
    if (relativeHeading <= -180.0)
    {
        relativeHeading += 360.0;
    }

    float delta = relativeHeading - _lastRelativeHeading;

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

    return continuousHeading;
}

void EvoIMU::getEuler(float *x, float *y, float *z)
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    *x = event.orientation.x;
    *y = event.orientation.y;
    *z = event.orientation.z;
}

float EvoIMU::getEulerX()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.x;
}

float EvoIMU::getEulerY()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.y;
}

float EvoIMU::getEulerZ()
{
    i2CDevice.selectChannel(_channel);
    bno.getEvent(&event);
    return event.orientation.z;
}
