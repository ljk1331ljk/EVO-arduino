#ifndef EVO_CONTROLLER_H
#define EVO_CONTROLLER_H

#include <Arduino.h>
#include "ControllerDefinition.h"

class EvoController
{
public:
    void begin();

    const char *getControllerName() const;
    EvoControllerId getControllerId() const;
    uint8_t getMotorCount() const;
    uint8_t getServoCount() const;
    uint8_t getGPIOCount() const;
    uint8_t getButtonCount() const;
    uint8_t getI2CChannelCount() const;

    bool hasRGBLed() const;
    bool hasDisplay() const;
    bool hasBuzzer() const;
    bool hasEV3SensorPorts() const;
    bool hasBatteryCharger() const;
    bool hasI2CMultiplexer() const;
    bool hasHC05() const;
    bool hasPWMMultiplexer() const;
    bool hasBootLed() const;
    bool hasShutdownPin() const;
    bool hasNSleepPin() const;

    void playTone(unsigned int frequency, int duration = -1, bool blocking = true);
    void stopTone();
};

#endif
