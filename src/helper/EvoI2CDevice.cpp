#include "EvoI2CDevice.h"

// Singleton instance
I2CDevice &I2CDevice::getInstance()
{
    static I2CDevice instance;
    return instance;
}

// Private constructor
I2CDevice::I2CDevice()
    : wire(Wire),
      muxAddr(SelectedEvoController::TCA9548A_ADDR),
      initialized(false),
      sdaPin(SelectedEvoController::SDA0_PIN),
      sclPin(SelectedEvoController::SCL0_PIN)
{
    initBus();
}

// Initialize I2C bus
void I2CDevice::initBus()
{
    if (!initialized)
    {
        wire.begin(sdaPin, sclPin);

        initialized = true;
        channelSelected = I2CChannel::I2CUNDEFINED;
    }
}

// Select the I2C channel based on the enum class
bool I2CDevice::selectChannel(I2CChannel channel)
{
    if (channel != channelSelected)
    {
        uint8_t channelNum = static_cast<uint8_t>(channel); // Convert enum to number
        wire.beginTransmission(muxAddr);
        wire.write(1 << channelNum);
        if (wire.endTransmission() == 0)
        {
            channelSelected = channel;
            return true;
        }
        return false;
    }
    return false;
}

// Get selected channel
uint8_t I2CDevice::getChannel()
{
    return static_cast<uint8_t>(channelSelected) + 1;
}

// Get I2C bus
TwoWire &I2CDevice::getBus()
{
    return wire;
}

bool I2CDevice::isI2CConnected(uint8_t address)
{
    wire.beginTransmission(address);
    return (wire.endTransmission() == 0);
}
