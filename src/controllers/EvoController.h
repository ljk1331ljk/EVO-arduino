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
    bool selectI2CChannel(I2CChannel channel);
    int scanI2CChannel(I2CChannel channel, uint8_t *addresses, int maxAddresses = 5);

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

    float getBattery();
    float getTopBattery();
    float getBottomBattery();

    void waitForButton();
    void waitForPress(int debounceMs = 0);
    void waitForRelease(int debounceMs = 0);
    void waitForBump(int debounceMs = 0);
    void waitForPress(uint8_t buttonNumber, int debounceMs);
    void waitForRelease(uint8_t buttonNumber, int debounceMs);
    void waitForBump(uint8_t buttonNumber, int debounceMs);
    ButtonState getButton(uint8_t buttonNumber = 1);

    void playTone(unsigned int frequency, int duration = -1, bool blocking = true);
    void stopTone();

    void flipDisplayOrientation(bool flip = true);
    void clearDisplay();
    void setFontSize(uint8_t size);
    void writeToDisplay(int value, int x, int y, bool clear = false, bool draw = false);
    void writeToDisplay(double value, int x, int y, bool clear = false, bool draw = false);
    void writeToDisplay(const char *value, int x, int y, bool clear = false, bool draw = false);
    void writeLineToDisplay(int value, int line, bool clear = false, bool draw = false);
    void writeLineToDisplay(double value, int line, bool clear = false, bool draw = false);
    void writeLineToDisplay(const char *value, int line, bool clear = false, bool draw = false);
    void drawDisplay();
    void drawPixel(int x, int y, bool clear = false, bool draw = false);
    void drawLine(int x0, int y0, int x1, int y1, bool clear = false, bool draw = false);
    void drawRect(int x, int y, int width, int height, bool fill = false, bool clear = false, bool draw = false);
    void drawCircle(int x, int y, int radius, bool fill = false, bool clear = false, bool draw = false);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool clear = false, bool draw = false);
};

#endif
