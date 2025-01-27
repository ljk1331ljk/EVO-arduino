#include "EvoI2CDevice.h"

// Singleton instance
I2CDevice &I2CDevice::getInstance(uint8_t muxAddress, int sda, int scl)
{
    static I2CDevice instance(muxAddress, sda, scl);
    return instance;
}

// Private constructor
I2CDevice::I2CDevice(uint8_t muxAddress, int sda, int scl)
    : wire(Wire), muxAddr(muxAddress), initialized(false), sdaPin(sda), sclPin(scl)
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