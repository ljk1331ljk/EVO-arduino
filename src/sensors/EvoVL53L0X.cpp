#include "EvoVL53L0X.h"

EvoVL53L0X::EvoVL53L0X(I2CChannel channel)
{
    _channel = channel;
}

bool EvoVL53L0X::begin(bool continuous)
{

    i2CDevice.selectChannel(_channel);
    if (!this->lox.begin())
    {
        return false;
    }
    if (continuous)
    {
        lox.startRangeContinuous(100);
        delay(50);
    }
    return true;
}

int EvoVL53L0X::getDistance()
{
    i2CDevice.selectChannel(_channel);
    lox.rangingTest(&this->measure, false); // pass in 'true' to get debug data printout!
    if (this->measure.RangeStatus != 4)
    {
        return this->measure.RangeMilliMeter;
    }
    return 2000;
}
int EvoVL53L0X::getDistanceContinuous()
{
    i2CDevice.selectChannel(_channel);
    if (lox.isRangeComplete())
    {
        return lox.readRangeResult();
    }
    return 2000;
}
