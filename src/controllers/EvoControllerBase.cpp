#include "EvoControllerBase.h"
const char *EvoControllerBase::getControllerName() const { return SelectedEvoController::NAME; }
EvoControllerId EvoControllerBase::getControllerId() const { return SelectedEvoController::ID; }
uint8_t EvoControllerBase::getMotorCount() const { return SelectedEvoController::MOTOR_COUNT; }
uint8_t EvoControllerBase::getServoCount() const { return SelectedEvoController::SERVO_COUNT; }
uint8_t EvoControllerBase::getGPIOCount() const { return SelectedEvoController::GPIO_COUNT; }
uint8_t EvoControllerBase::getButtonCount() const { return SelectedEvoController::BUTTON_COUNT; }
uint8_t EvoControllerBase::getI2CChannelCount() const { return SelectedEvoController::I2C_CHANNEL_COUNT; }
bool EvoControllerBase::hasRGBLed() const { return SelectedEvoController::HAS_RGB_LED; }
bool EvoControllerBase::hasDisplay() const { return SelectedEvoController::HAS_DISPLAY; }
bool EvoControllerBase::hasBuzzer() const { return SelectedEvoController::HAS_BUZZER; }
bool EvoControllerBase::hasEV3SensorPorts() const { return SelectedEvoController::HAS_EV3_SENSOR_PORTS; }
bool EvoControllerBase::hasBatteryCharger() const { return SelectedEvoController::HAS_BATTERY_CHARGER; }
bool EvoControllerBase::hasI2CMultiplexer() const { return SelectedEvoController::HAS_I2C_MULTIPLEXER; }
bool EvoControllerBase::hasHC05() const { return SelectedEvoController::HAS_HC05; }
bool EvoControllerBase::hasPWMMultiplexer() const { return SelectedEvoController::HAS_PWM_MULTIPLEXER; }
bool EvoControllerBase::hasBootLed() const { return SelectedEvoController::HAS_BOOT_LED; }
bool EvoControllerBase::hasShutdownPin() const { return SelectedEvoController::HAS_SHUTDOWN_PIN; }
bool EvoControllerBase::hasNSleepPin() const { return SelectedEvoController::HAS_NSLEEP_PIN; }
