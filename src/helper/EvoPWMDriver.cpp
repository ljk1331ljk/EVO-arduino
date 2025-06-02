#include "EvoPWMDriver.h"

void EvoPWMDriver::begin()
{
    if (!begun)
    {
        pwm.begin();
        pwm.reset();
        pwm.setOscillatorFrequency(27000000);
        pwm.setPWMFreq(2500);
        begun = true;
    }
}

void EvoPWMDriver::setPWM(uint8_t channel, uint16_t on, uint16_t off)
{
    if (channel > 15)
        return; // Validate the channel (0-15)

    pwm.setPWM(channel, on, off);
}

void EvoPWMDriver::setPin(uint8_t num, uint16_t val, bool invert)
{
    pwm.setPin(num, val, invert);
}
void EvoPWMDriver::setPWMFreq(int freq)
{
    if (freq == _freq)
        return; // No change in frequency
    _freq = freq;
    if (freq < 50 || freq > 3500)
        return; // Validate the frequency (50-3500 Hz)

    pwm.setPWMFreq(_freq);
}