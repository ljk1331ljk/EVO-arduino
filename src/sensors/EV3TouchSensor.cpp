#include "EV3TouchSensor.h"

namespace
{
template <typename Board>
int getEV3TouchPin(SensorPort port)
{
    if constexpr (Board::HAS_EV3_SENSOR_PORTS)
    {
        switch (port)
        {
        case S1: return Board::S11;
        case S2: return Board::S21;
        case S3: return Board::S31;
        case S4: return Board::S41;
        }
    }
    return -1;
}
}

EV3TouchSensor::EV3TouchSensor(SensorPort port) : _port(port)
{
    _pin = getEV3TouchPin<SelectedEvoController>(_port);
    if (_pin >= 0)
        pinMode(_pin, INPUT_PULLDOWN);
}
int EV3TouchSensor::getButton()
{
    if (_pin < 0)
        return 0;
    return digitalRead(_pin);
}
void EV3TouchSensor::waitForPress(int debouncems)
{
    if (_pin < 0)
        return;
    while (!getButton())
        delay(10);
    delay(debouncems);
}
void EV3TouchSensor::waitForRelease(int debouncems)
{
    if (_pin < 0)
        return;
    while (getButton())
        delay(10);
    delay(debouncems);
}

void EV3TouchSensor::waitForBump(int debouncems)
{
    if (_pin < 0)
        return;
    waitForPress(debouncems);
    waitForRelease(debouncems);
}
