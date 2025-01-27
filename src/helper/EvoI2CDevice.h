#ifndef EVO_I2C_DEVICE_H
#define EVO_I2C_DEVICE_H
#include <Arduino.h>
#include <Wire.h>

enum I2CChannel
{
    I2CUNDEFINED = -1,
    I2C1 = 0, // Channel 0 on the multiplexer
    I2C2 = 1, // Channel 1 on the multiplexer
    I2C3 = 2, // Channel 2 on the multiplexer
    I2C4 = 3, // Channel 3 on the multiplexer
    I2C5 = 4, // Channel 4 on the multiplexer
    I2C6 = 5, // Channel 5 on the multiplexer
    I2C7 = 6, // Channel 6 on the multiplexer
    I2C8 = 7  // Channel 7 on the multiplexer
};

class I2CDevice
{
public:
    // Singleton pattern to get the I2CDevice instance
    static I2CDevice &getInstance(uint8_t muxAddress = 0x70, int sda = 1, int scl = 2);

    // Method to select the I2C channel on the multiplexer
    bool selectChannel(I2CChannel channel);

    // Method to get selected channel on the multiplexor
    uint8_t getChannel();
    // Method to check if device is connected
    bool isI2CConnected(uint8_t address);

    // Get the I2C bus instance
    TwoWire &getBus();

private:
    I2CDevice(uint8_t muxAddress = 0x70, int sda = 1, int scl = 2); // Private constructor
    I2CDevice(const I2CDevice &) = delete;                          // Delete copy constructor
    I2CDevice &operator=(const I2CDevice &) = delete;               // Delete assignment operator

    TwoWire &wire;    // Reference to the I2C bus (Wire or Wire1)
    uint8_t muxAddr;  // Address of the I2C multiplexer
    bool initialized; // Flag to check if the I2C bus has been initialized
    int sdaPin;       // SDA pin
    int sclPin;       // SCL pin
    I2CChannel channelSelected;
    void initBus(); // Private method to initialize the I2C bus
};

#endif