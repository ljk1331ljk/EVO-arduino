#ifndef EVO_I2C_DEVICE_H
#define EVO_I2C_DEVICE_H
#include <Arduino.h>
#include <Wire.h>
#include "../controllers/ControllerDefinition.h"

class I2CDevice
{
public:
    // Singleton pattern to get the I2CDevice instance
    static I2CDevice &getInstance();

    // Method to select the I2C channel on the multiplexer
    bool selectChannel(I2CChannel channel);

    // Method to get selected channel on the multiplexor
    uint8_t getChannel();
    // Method to check if device is connected
    bool isI2CConnected(uint8_t address);

    // Get the I2C bus instance
    TwoWire &getBus();

private:
    I2CDevice();
    I2CDevice(const I2CDevice &) = delete;                          // Delete copy constructor
    I2CDevice &operator=(const I2CDevice &) = delete;               // Delete assignment operator

    TwoWire &wire;    // Reference to the I2C bus (Wire or Wire1)
    uint8_t muxAddr;  // Address of the I2C multiplexer
    bool initialized; // Flag to check if the I2C bus has been initialized
    int sdaPin;       // SDA pin
    int sclPin;       // SCL pin
    I2CChannel channelSelected;
    uint8_t selectedMuxChannel;
    void initBus(); // Private method to initialize the I2C bus
    uint8_t getMuxChannel(I2CChannel channel) const;
};

#endif
