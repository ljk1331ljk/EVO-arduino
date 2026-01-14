#include "EV3TouchSensor.h"

EV3TouchSensor::EV3TouchSensor(SensorPort port) : _port(port)
{
    switch (_port)
    {
    case S1:
        _pin = S11;
        break;
    case S2:
        _pin = S21;
        break;
    case S3:
        _pin = S31;
        break;
    case S4:
        _pin = S41;
        break;
    }
    pinMode(_pin, INPUT_PULLDOWN);
}
int EV3TouchSensor::getButton()
{
    return digitalRead(_pin);
}
void EV3TouchSensor::waitForPress(int debouncems)
{
    while (!getButton())
        delay(10);
    delay(debouncems);
}
void EV3TouchSensor::waitForRelease(int debouncems)
{
    while (getButton())
        delay(10);
    delay(debouncems);
}

void EV3TouchSensor::waitForBump(int debouncems)
{
    waitForPress(debouncems);
    waitForRelease(debouncems);
}
