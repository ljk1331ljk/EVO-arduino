#include "EV3TouchSensor.h"

EV3TouchSensor::EV3TouchSensor(SensorPort port) : _port(port)
{
    const EvoControllerConfig &config = EvoControllerConfigManager::getInstance().getConfig();
    uint8_t portIndex = static_cast<uint8_t>(_port);
    if (portIndex >= config.sensorPortCount)
    {
        portIndex = 0;
    }

    _pin = config.sensorPorts[portIndex].digitalPin;
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
