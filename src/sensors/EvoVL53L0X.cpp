#include "EvoVL53L0X.h"

EvoVL53L0X::EvoVL53L0X(I2CChannel channel)
{
    _channel = channel;
}

void EvoVL53L0X::begin()
{

    i2CDevice.selectChannel(_channel);
    if (!this->lox.begin())
    {
        Serial.println(F("Failed to boot VL53L0X"));
    }
}

int EvoVL53L0X::getDistance()
{
    i2CDevice.selectChannel(_channel);
    lox.rangingTest(&this->measure, false); // pass in 'true' to get debug data printout!
    if (this->measure.RangeStatus != 4)
    {
        return this->measure.RangeMilliMeter;
    }
    return 10000;
}
