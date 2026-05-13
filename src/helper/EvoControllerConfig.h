#ifndef EVO_CONTROLLER_CONFIG_H
#define EVO_CONTROLLER_CONFIG_H

#include <Arduino.h>
#include "EvoI2CDevice.h"

constexpr uint8_t EVO_MAX_MOTOR_PORTS = 8;
constexpr uint8_t EVO_MAX_SENSOR_PORTS = 8;
constexpr uint8_t EVO_MAX_SERVO_PORTS = 16;
constexpr uint8_t EVO_MAX_I2C_PORTS = 8;
constexpr uint8_t EVO_MAX_GPIO_PORTS = 16;

struct EvoMotorPortConfig
{
    uint8_t power1 = 0;
    uint8_t power2 = 0;
    uint8_t tach1 = 0;
    uint8_t tach2 = 0;
};

struct EvoSensorPortConfig
{
    uint8_t txPin = 0;
    uint8_t rxPin = 0;
    uint8_t digitalPin = 0;
};

enum class EvoControllerVariant
{
    EvoX1E,
    EvoX1P,
    EvoX1R,
    Custom,
};

struct EvoControllerConfig
{
    const char *name = "EvoX1E";

    uint8_t motorPortCount = 0;
    uint8_t sensorPortCount = 0;
    uint8_t servoPortCount = 0;
    uint8_t i2cPortCount = 0;
    uint8_t gpioPortCount = 0;

    bool hasBuzzer = false;
    bool hasNeoPixel = false;
    bool hasDisplay = true;

    uint8_t buzzerPin = 0;
    uint8_t buttonPin = 0;
    uint8_t pixelPin = 0;
    I2CChannel displayChannel = I2C8;

    uint8_t i2cSdaPin = 1;
    uint8_t i2cSclPin = 2;
    uint8_t muxAddress = 0x70;

    EvoMotorPortConfig motorPorts[EVO_MAX_MOTOR_PORTS];
    EvoSensorPortConfig sensorPorts[EVO_MAX_SENSOR_PORTS];
    uint8_t servoChannels[EVO_MAX_SERVO_PORTS];
    I2CChannel i2cChannels[EVO_MAX_I2C_PORTS];
    uint8_t gpioPins[EVO_MAX_GPIO_PORTS];
};

class EvoControllerConfigManager
{
public:
    static EvoControllerConfigManager &getInstance();

    const EvoControllerConfig &getConfig() const;
    void setVariant(EvoControllerVariant variant);
    void setCustomConfig(const EvoControllerConfig &config);

private:
    EvoControllerConfigManager();

    EvoControllerConfig _activeConfig;
    EvoControllerVariant _variant = EvoControllerVariant::EvoX1E;

    EvoControllerConfig createEvoX1EConfig() const;
    EvoControllerConfig createEvoX1PConfig() const;
    EvoControllerConfig createEvoX1RConfig() const;
};

#endif
