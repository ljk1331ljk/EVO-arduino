#include "EvoServo.h"

EvoServo::EvoServo(ServoChannel servoChannel, ServoType servoType)
{
    const EvoControllerConfig &config = EvoControllerConfigManager::getInstance().getConfig();
    uint8_t requestedChannel = static_cast<uint8_t>(servoChannel);
    if (requestedChannel >= config.servoPortCount)
    {
        requestedChannel = 0;
    }
    _useGPIODirect = (config.servoControlMethod == EvoServoControlMethod::GPIODirect);
    if (_useGPIODirect)
    {
        _servoPin = config.servoGPIOPins[requestedChannel];
        _gpioChannel = requestedChannel % 16;
    }
    else
    {
        _servoChannel = config.servoChannels[requestedChannel];
    }
    switch (servoType)
    {
    case SG90:
        setPulse(300, 1200);
        setRange(0, 180);
        break;
    case GeekServo360Grey:
        setPulse(200, 1100);
        setRange(0, 360);
        break;
    case GeekServo360Orange:
        setPulse(200, 980);
        setRange(0, 360);
        break;
    case GeekServoContinuous:
        setPulse(180, 1040);
        setRange(-100, 100);
        break;
    case Default:
        setPulse(300, 1200);
        setRange(0, 180);
        break;
    }
}

void EvoServo::begin()
{
    if (_useGPIODirect)
    {
#if defined(ARDUINO_ARCH_ESP32)
        ledcSetup(_gpioChannel, 50, 16);
        ledcAttachPin(_servoPin, _gpioChannel);
#endif
    }
    else
    {
        driver.begin();
    }
}
void EvoServo::setPulse(int minPulse, int maxPulse)
{
    _minPulse = minPulse;
    _maxPulse = maxPulse;
}
void EvoServo::setRange(int minRange, int maxRange)
{
    _minRange = minRange;
    _maxRange = maxRange;
}
void EvoServo::write(int position)
{
    int pulse = map(position, _minRange, _maxRange, _minPulse, _maxPulse);
    if (_useGPIODirect)
    {
#if defined(ARDUINO_ARCH_ESP32)
        uint32_t duty = map(pulse, 0, 20000, 0, 65535);
        ledcWrite(_gpioChannel, duty);
#endif
        return;
    }
    driver.setPWMFreq(100);
    driver.setPWM(_servoChannel, 0, pulse);
}

void EvoServo::setPWM(int on, int off)
{
    if (_useGPIODirect)
    {
#if defined(ARDUINO_ARCH_ESP32)
        uint32_t duty = map(off, 0, 20000, 0, 65535);
        ledcWrite(_gpioChannel, duty);
#endif
        return;
    }
    driver.setPWMFreq(100);
    driver.setPWM(_servoChannel, on, off);
}
