#include "EvoServo.h"

EvoServo::EvoServo(ServoChannel servoChannel, ServoType servoType)
{
    _servoChannel = static_cast<uint8_t>(servoChannel);
    switch (servoType)
    {
    case SG90:
        setPulse(300, 1200);
        setRange(0, 180);
        break;
    case GeekServo360Grey:
        setPulse(200, 980);
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
    driver.begin();
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
    driver.setPWM(_servoChannel, 0, map(position, _minRange, _maxRange, _minPulse, _maxPulse));
}
void EvoServo::setPWM(int on, int off)
{
    driver.setPWM(_servoChannel, on, off);
}