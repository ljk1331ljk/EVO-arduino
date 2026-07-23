#ifndef EVO_CONTROLLER_BASE_H
#define EVO_CONTROLLER_BASE_H

#include <Arduino.h>
#include <boards/SelectedBoard.h>
#include <helper/Tones.h>
#include <helper/EvoI2CDevice.h>
#include <helper/EvoPWMDriver.h>
#include <helper/EvoBQ25887.h>
#include <helper/AdafruitSensors/Adafruit_NeoPixel.h>
#include <helper/U8g2/U8g2lib.h>

enum ButtonState
{
    PRESSED,
    RELEASED
};

enum PinState
{
    BUTTON_STATE,
    RGB_LED_STATE
};

class EvoControllerBase
{
private:
    Adafruit_NeoPixel rgb;
    uint8_t _fontSize = 8;
    PinState pinState = RGB_LED_STATE;

    I2CDevice &i2CDevice = I2CDevice::getInstance();
    EvoPWMDriver &evoPWMDriver = EvoPWMDriver::getInstance();

    EvoControllerBase(const EvoControllerBase &) = delete;
    EvoControllerBase &operator=(const EvoControllerBase &) = delete;

protected:
    EvoControllerBase();

public:
    virtual ~EvoControllerBase() = default;

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;
    EvoBQ25887 charger;

    void begin();

    const char *getBoardName() const;
    EvoBoardId getBoardId() const;

    void selectI2CChannel(I2CChannel channel);
    int scanI2CChannel(
        I2CChannel channel,
        uint8_t *addresses,
        int maxAddresses = 5
    );

    float getTopBattery();
    float getBottomBattery();
    float getBattery();

    void flipDisplayOrientation(bool flip = true);
    void clearDisplay();

    void writeToDisplay(
        int value,
        int x,
        int y,
        bool clear = false,
        bool draw = false
    );

    void writeToDisplay(
        double value,
        int x,
        int y,
        bool clear = false,
        bool draw = false
    );

    void writeToDisplay(
        const char *text,
        int x,
        int y,
        bool clear = false,
        bool draw = false
    );

    void writeLineToDisplay(
        int value,
        int line,
        bool clear = false,
        bool draw = false
    );

    void writeLineToDisplay(
        double value,
        int line,
        bool clear = false,
        bool draw = false
    );

    void writeLineToDisplay(
        const char *text,
        int line,
        bool clear = false,
        bool draw = false
    );

    void drawDisplay();
    void setFontSize(uint8_t size);

    void waitForButton();
    void waitForPress(int debounceMs = 0);
    void waitForRelease(int debounceMs = 0);
    void waitForBump(int debounceMs = 0);
    ButtonState getButton();

    void playTone(
        uint frequency,
        int duration = -1,
        bool blocking = true
    );

    void stopTone();
    void setRGB(int red, int green, int blue);
};

#endif
