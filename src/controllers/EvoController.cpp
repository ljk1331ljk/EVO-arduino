#include "EvoController.h"
#include "SelectedController.h"
#include "../helper/EvoBQ25887.h"
#include "../helper/EvoPWMDriver.h"
#include "../helper/EvoI2CDevice.h"
#include "../helper/U8g2/U8g2lib.h"
#include <Wire.h>

namespace
{
EvoBQ25887 &batteryCharger()
{
    static EvoBQ25887 charger;
    return charger;
}

U8G2_SSD1306_128X64_NONAME_F_HW_I2C &onboardDisplay()
{
    static U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);
    return display;
}

uint8_t &onboardDisplayFontSize()
{
    static uint8_t fontSize = 8;
    return fontSize;
}

template <typename Board>
bool selectOnboardDisplay()
{
    if constexpr (Board::HAS_DISPLAY)
    {
        return I2CDevice::getInstance().selectChannel(
            static_cast<I2CChannel>(Board::DISPLAY_I2C_PORT));
    }
    return false;
}

template <typename Board>
void initializeOnboardDisplay()
{
    if constexpr (Board::HAS_DISPLAY)
    {
        selectOnboardDisplay<Board>();
        onboardDisplay().setI2CAddress(Board::SSD1309_ADDR << 1);
        onboardDisplay().begin();
    }
}

template <typename Board>
void initializeOptionalPins()
{
    if constexpr (Board::HAS_BOOT_LED)
    {
        pinMode(Board::BOOT_LED_PIN, OUTPUT);
    }
    if constexpr (Board::HAS_SHUTDOWN_PIN)
    {
        pinMode(Board::SHUTDOWN_PIN, OUTPUT);
    }
    if constexpr (Board::HAS_NSLEEP_PIN)
    {
        pinMode(Board::NSLEEP_PIN, OUTPUT);
        digitalWrite(Board::NSLEEP_PIN, HIGH);
    }
}

bool getOnboardButtonPin(uint8_t buttonNumber, uint8_t &pin)
{
    if (buttonNumber == 0 || buttonNumber > SelectedEvoController::BUTTON_COUNT)
        return false;

    pin = SelectedEvoController::buttonPin(buttonNumber - 1);
    return true;
}
}

void EvoController::begin()
{
    Wire.begin(SelectedEvoController::SDA0_PIN, SelectedEvoController::SCL0_PIN);
    Wire1.begin(SelectedEvoController::SDA1_PIN, SelectedEvoController::SCL1_PIN);

    if constexpr (SelectedEvoController::HAS_PWM_MULTIPLEXER)
    {
        EvoPWMDriver::getInstance().begin();
    }

    if constexpr (SelectedEvoController::HAS_BATTERY_CHARGER)
    {
        batteryCharger().begin();
    }

    initializeOptionalPins<SelectedEvoController>();
    for (uint8_t button = 0; button < SelectedEvoController::BUTTON_COUNT; ++button)
    {
        pinMode(SelectedEvoController::buttonPin(button), INPUT_PULLUP);
    }
    initializeOnboardDisplay<SelectedEvoController>();
    setFontSize(8);
}

const char *EvoController::getControllerName() const { return SelectedEvoController::NAME; }
EvoControllerId EvoController::getControllerId() const { return SelectedEvoController::ID; }
uint8_t EvoController::getMotorCount() const { return SelectedEvoController::MOTOR_COUNT; }
uint8_t EvoController::getServoCount() const { return SelectedEvoController::SERVO_COUNT; }
uint8_t EvoController::getGPIOCount() const { return SelectedEvoController::GPIO_COUNT; }
uint8_t EvoController::getButtonCount() const { return SelectedEvoController::BUTTON_COUNT; }
uint8_t EvoController::getI2CChannelCount() const { return SelectedEvoController::I2C_CHANNEL_COUNT; }
bool EvoController::hasRGBLed() const { return SelectedEvoController::HAS_RGB_LED; }
bool EvoController::hasDisplay() const { return SelectedEvoController::HAS_DISPLAY; }
bool EvoController::hasBuzzer() const { return SelectedEvoController::HAS_BUZZER; }
bool EvoController::hasEV3SensorPorts() const { return SelectedEvoController::HAS_EV3_SENSOR_PORTS; }
bool EvoController::hasBatteryCharger() const { return SelectedEvoController::HAS_BATTERY_CHARGER; }
bool EvoController::hasI2CMultiplexer() const { return SelectedEvoController::HAS_I2C_MULTIPLEXER; }
bool EvoController::hasHC05() const { return SelectedEvoController::HAS_HC05; }
bool EvoController::hasPWMMultiplexer() const { return SelectedEvoController::HAS_PWM_MULTIPLEXER; }
bool EvoController::hasBootLed() const { return SelectedEvoController::HAS_BOOT_LED; }
bool EvoController::hasShutdownPin() const { return SelectedEvoController::HAS_SHUTDOWN_PIN; }
bool EvoController::hasNSleepPin() const { return SelectedEvoController::HAS_NSLEEP_PIN; }

float EvoController::getBattery()
{
    if constexpr (SelectedEvoController::HAS_BATTERY_CHARGER)
    {
        batteryCharger().wdReset();
        batteryCharger().setADC_EN(true);
        batteryCharger().pollAllRegs();
        return batteryCharger().getADC_VBAT();
    }
    return 0.0f;
}

float EvoController::getTopBattery()
{
    if constexpr (SelectedEvoController::HAS_BATTERY_CHARGER)
    {
        batteryCharger().wdReset();
        batteryCharger().setADC_EN(true);
        batteryCharger().pollAllRegs();
        return batteryCharger().getADC_VCELLTOP();
    }
    return 0.0f;
}

float EvoController::getBottomBattery()
{
    if constexpr (SelectedEvoController::HAS_BATTERY_CHARGER)
    {
        batteryCharger().wdReset();
        batteryCharger().setADC_EN(true);
        batteryCharger().pollAllRegs();
        return batteryCharger().getADC_VCELLBOT();
    }
    return 0.0f;
}

void EvoController::waitForButton()
{
    waitForBump(1, 0);
}

void EvoController::waitForPress(int debounceMs)
{
    waitForPress(1, debounceMs);
}

void EvoController::waitForRelease(int debounceMs)
{
    waitForRelease(1, debounceMs);
}

void EvoController::waitForBump(int debounceMs)
{
    waitForBump(1, debounceMs);
}

void EvoController::waitForPress(uint8_t buttonNumber, int debounceMs)
{
    uint8_t pin;
    if (!getOnboardButtonPin(buttonNumber, pin))
        return;

    while (digitalRead(pin) != LOW)
    {
    }
    delay(debounceMs);
}

void EvoController::waitForRelease(uint8_t buttonNumber, int debounceMs)
{
    uint8_t pin;
    if (!getOnboardButtonPin(buttonNumber, pin))
        return;

    while (digitalRead(pin) == LOW)
    {
    }
    delay(debounceMs);
}

void EvoController::waitForBump(uint8_t buttonNumber, int debounceMs)
{
    waitForPress(buttonNumber, debounceMs);
    waitForRelease(buttonNumber, debounceMs);
}

ButtonState EvoController::getButton(uint8_t buttonNumber)
{
    uint8_t pin;
    if (!getOnboardButtonPin(buttonNumber, pin))
        return RELEASED;

    return digitalRead(pin) == LOW ? PRESSED : RELEASED;
}

void EvoController::playTone(unsigned int frequency, int duration, bool blocking)
{
    if constexpr (SelectedEvoController::HAS_BUZZER)
    {
        if (duration == 0)
            return;

        tone(SelectedEvoController::BUZZER_PIN, frequency, duration < 0 ? 0 : duration);
        if (blocking && duration > 0)
        {
            delay(duration);
            noTone(SelectedEvoController::BUZZER_PIN);
        }
    }
}

void EvoController::stopTone()
{
    if constexpr (SelectedEvoController::HAS_BUZZER)
    {
        noTone(SelectedEvoController::BUZZER_PIN);
    }
}

void EvoController::flipDisplayOrientation(bool flip)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    onboardDisplay().setFlipMode(flip);
}

void EvoController::clearDisplay()
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    onboardDisplay().clearBuffer();
}

void EvoController::setFontSize(uint8_t size)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;

    onboardDisplayFontSize() = size;
    onboardDisplay().setFontPosTop();
    switch (size)
    {
    case 4: onboardDisplay().setFont(u8g2_font_minimal3x3_tu); break;
    case 5: onboardDisplay().setFont(u8g2_font_u8glib_4_tf); break;
    case 6: onboardDisplay().setFont(u8g2_font_tiny5_tf); break;
    case 7: onboardDisplay().setFont(u8g2_font_5x7_tf); break;
    case 8: onboardDisplay().setFont(u8g2_font_6x10_tf); break;
    case 9: onboardDisplay().setFont(u8g2_font_profont12_tf); break;
    case 10: onboardDisplay().setFont(u8g2_font_6x13_tf); break;
    default:
        onboardDisplayFontSize() = 7;
        onboardDisplay().setFont(u8g2_font_5x7_tf);
        break;
    }
}

void EvoController::writeToDisplay(int value, int x, int y, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().setCursor(x, y);
    onboardDisplay().print(value);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::writeToDisplay(double value, int x, int y, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().setCursor(x, y);
    onboardDisplay().print(value);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::writeToDisplay(const char *value, int x, int y, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().setCursor(x, y);
    onboardDisplay().print(value);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::writeLineToDisplay(int value, int line, bool clear, bool draw)
{
    writeToDisplay(value, 0, line * onboardDisplayFontSize(), clear, draw);
}

void EvoController::writeLineToDisplay(double value, int line, bool clear, bool draw)
{
    writeToDisplay(value, 0, line * onboardDisplayFontSize(), clear, draw);
}

void EvoController::writeLineToDisplay(const char *value, int line, bool clear, bool draw)
{
    writeToDisplay(value, 0, line * onboardDisplayFontSize(), clear, draw);
}

void EvoController::drawDisplay()
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    onboardDisplay().sendBuffer();
}

void EvoController::drawPixel(int x, int y, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().drawPixel(x, y);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::drawLine(int x0, int y0, int x1, int y1, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().drawLine(x0, y0, x1, y1);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::drawRect(int x, int y, int width, int height, bool fill, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    if (fill)
        onboardDisplay().drawBox(x, y, width, height);
    else
        onboardDisplay().drawFrame(x, y, width, height);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::drawCircle(int x, int y, int radius, bool fill, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    if (fill)
        onboardDisplay().drawDisc(x, y, radius);
    else
        onboardDisplay().drawCircle(x, y, radius);
    if (draw)
        onboardDisplay().sendBuffer();
}

void EvoController::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool clear, bool draw)
{
    if (!selectOnboardDisplay<SelectedEvoController>())
        return;
    if (clear)
        onboardDisplay().clearBuffer();
    onboardDisplay().drawTriangle(x0, y0, x1, y1, x2, y2);
    if (draw)
        onboardDisplay().sendBuffer();
}
