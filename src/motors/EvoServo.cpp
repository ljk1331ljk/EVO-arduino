#include "EvoServo.h"

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