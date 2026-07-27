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
      sclPin(SelectedEvoController::SCL0_PIN),
      selectedMuxChannel(0xFF)
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
    const int logicalChannel = static_cast<int>(channel);
    if (logicalChannel < 0 || logicalChannel >= SelectedEvoController::I2C_CHANNEL_COUNT)
        return false;

    if (channel != channelSelected)
    {
        const uint8_t channelNum = getMuxChannel(channel);
        wire.beginTransmission(muxAddr);
        wire.write(1 << channelNum);
        if (wire.endTransmission() == 0)
        {
            channelSelected = channel;
            selectedMuxChannel = channelNum;
            return true;
        }
        return false;
    }
    return true;
}

uint8_t I2CDevice::getMuxChannel(I2CChannel channel) const
{
    switch (channel)
    {
    case I2C1: return SelectedEvoController::I2C1;
    case I2C2: return SelectedEvoController::I2C2;
    case I2C3: return SelectedEvoController::I2C3;
    case I2C4: return SelectedEvoController::I2C4;
    case I2C5: return SelectedEvoController::I2C5;
    case I2C6: return SelectedEvoController::I2C6;
    case I2C7: return SelectedEvoController::I2C7;
    case I2C8: return SelectedEvoController::I2C8;
    default: return 0xFF;
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
