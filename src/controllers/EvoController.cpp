#include "EvoController.h"
#include "SelectedController.h"
#include "../helper/EvoPWMDriver.h"
#include <Wire.h>

namespace
{
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
}

void EvoController::begin()
{
    Wire.begin(SelectedEvoController::SDA0_PIN, SelectedEvoController::SCL0_PIN);
    Wire1.begin(SelectedEvoController::SDA1_PIN, SelectedEvoController::SCL1_PIN);

    if constexpr (SelectedEvoController::HAS_PWM_MULTIPLEXER)
    {
        EvoPWMDriver::getInstance().begin();
    }

    initializeOptionalPins<SelectedEvoController>();
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
