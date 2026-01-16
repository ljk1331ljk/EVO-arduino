#include "EvoTOF.h"

EvoTOF::EvoTOF(I2CChannel channel)
{
    _channel = channel;
}

bool EvoTOF::begin(bool continuous)
{

    i2CDevice.selectChannel(_channel);
    if (!this->lox.init())
    {
        return false;
    }
    if (continuous)
    {
        lox.startContinuous();
        delay(50);
    }
    return true;
}

int EvoTOF::getDistance()
{
    i2CDevice.selectChannel(_channel);
    if (lox.timeoutOccurred())
    {
        return -1;
    }
    else
    {
        return lox.readRangeSingleMillimeters();
    }
}
int EvoTOF::getDistanceContinuous()
{
    i2CDevice.selectChannel(_channel);
    if (lox.timeoutOccurred())
    {
        return -1;
    }
    else
    {
        return lox.readRangeContinuousMillimeters();
    }
}

void EvoTOF::setLongRange(bool enable)
{
    i2CDevice.selectChannel(_channel);
    if (enable)
    {
        lox.setSignalRateLimit(0.1);
        lox.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
        lox.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
    }
    else
    {
        // restore default settings
        lox.setSignalRateLimit(0.25);
        lox.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 14);
        lox.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 10);
    }
}

void EvoTOF::setHighAccuracyMode()
{
    i2CDevice.selectChannel(_channel);
    // increase timing budget to 200 ms (default is about 33 ms)
    lox.setMeasurementTimingBudget(200000);
}

void EvoTOF::setHighSpeedMode()
{
    i2CDevice.selectChannel(_channel);
    // decrease timing budget to 20 ms
    lox.setMeasurementTimingBudget(20000);
}
