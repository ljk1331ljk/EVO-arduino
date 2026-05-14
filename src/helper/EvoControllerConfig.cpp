#include "EvoControllerConfig.h"

EvoControllerConfig makeEvoX1EConfig()
{
    EvoControllerConfig config;
    config.name = "EvoX1E";
    config.motorPortCount = 4;
    config.sensorPortCount = 4;
    config.servoPortCount = 8;
    config.i2cPortCount = 8;
    config.gpioPortCount = 8;
    config.servoControlMethod = EvoServoControlMethod::Multiplexor;

    config.hasBuzzer = true;
    config.hasNeoPixel = true;
    config.hasDisplay = true;

    config.buzzerPin = 11;
    config.buttonCount = 1;
    config.buttonPins[0] = 14;
    config.pixelPin = 14;
    config.displayChannel = I2C8;

    config.i2cSdaPin = 1;
    config.i2cSclPin = 2;
    config.muxAddress = 0x70;

    config.motorPorts[0] = {14, 15, 47, 21};
    config.motorPorts[1] = {13, 12, 38, 48};
    config.motorPorts[2] = {11, 10, 40, 39};
    config.motorPorts[3] = {9, 8, 42, 41};

    config.sensorPorts[0] = {10, 9};
    config.sensorPorts[1] = {8, 3};
    config.sensorPorts[2] = {7, 6};
    config.sensorPorts[3] = {5, 4};

    for (uint8_t i = 0; i < config.servoPortCount; i++)
    {
        config.servoChannels[i] = i;
        config.servoGPIOPins[i] = 0;
    }

    for (uint8_t i = 0; i < config.i2cPortCount; i++)
    {
        config.i2cChannels[i] = static_cast<I2CChannel>(i);
    }

    config.gpioPins[0] = 10;
    config.gpioPins[1] = 9;
    config.gpioPins[2] = 8;
    config.gpioPins[3] = 3;
    config.gpioPins[4] = 7;
    config.gpioPins[5] = 6;
    config.gpioPins[6] = 5;
    config.gpioPins[7] = 4;

    return config;
}

EvoControllerConfig makeEvoX1PConfig()
{
    EvoControllerConfig config = makeEvoX1EConfig();
    config.name = "EvoX1P";
    return config;
}

EvoControllerConfigManager &EvoControllerConfigManager::getInstance()
{
    static EvoControllerConfigManager instance;
    return instance;
}

EvoControllerConfigManager::EvoControllerConfigManager()
{
    _activeConfig = makeEvoX1EConfig();
}

const EvoControllerConfig &EvoControllerConfigManager::getConfig() const
{
    return _activeConfig;
}

void EvoControllerConfigManager::setCustomConfig(const EvoControllerConfig &config)
{
    _activeConfig = config;
}
