#ifndef EVO_PWM_DRIVER_H
#define EVO_PWM_DRIVER_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class EvoPWMDriver
{

public:
    EvoPWMDriver() : pwm(0x40, Wire1)
    {
    }
    static EvoPWMDriver &getInstance()
    {
        static EvoPWMDriver instance;
        return instance;
    }

    void begin();
    void setPWM(uint8_t channel, uint16_t on, uint16_t off);
    void setPin(uint8_t num, uint16_t val, bool invert = false);
    void setPWMFreq(int freq);

private:
    EvoPWMDriver(const EvoPWMDriver &) = delete;
    bool begun = false;
    int _freq = 2500; // Default frequency
    static EvoPWMDriver *instance;
    Adafruit_PWMServoDriver pwm;
};

#endif