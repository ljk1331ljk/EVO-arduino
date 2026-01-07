#include "EvoPWMDriver.h"

void EvoPWMDriver::begin()
{
    xSemaphoreTake(_mutex, portMAX_DELAY);
    if (!begun)
    {
        pwm.begin();
        pwm.reset();
        pwm.setOscillatorFrequency(27000000);
        pwm.setPWMFreq(2500);
        begun = true;
    }
    xSemaphoreGive(_mutex);
}

void EvoPWMDriver::setPWM(uint8_t channel, uint16_t on, uint16_t off)
{
    if (channel > 15)
        return; // Validate the channel (0-15)

    xSemaphoreTake(_mutex, portMAX_DELAY);
    pwm.setPWM(channel, on, off);
    xSemaphoreGive(_mutex);
}

void EvoPWMDriver::setPin(uint8_t num, uint16_t val, bool invert)
{
    xSemaphoreTake(_mutex, portMAX_DELAY);
    pwm.setPin(num, val, invert);
    xSemaphoreGive(_mutex);
}
void EvoPWMDriver::setPWMFreq(int freq)
{
    xSemaphoreTake(_mutex, portMAX_DELAY);
    if (freq != _freq)
    {
        pwm.setPWMFreq(_freq);
        _freq = freq;
    }
    xSemaphoreGive(_mutex);
}