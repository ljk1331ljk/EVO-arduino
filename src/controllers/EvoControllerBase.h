#ifndef EVO_CONTROLLER_BASE_H
#define EVO_CONTROLLER_BASE_H
#include <Arduino.h>
#include "ControllerDefinition.h"
#include "SelectedController.h"
class EvoControllerBase {
public:
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
};
#endif
