
#ifndef EVOLINELEADER_H
#define EVOLINELEADER_H

#include "../helper/EvoI2CDevice.h"

#define SYSTEM_STATUS_REGISTER 0x00 // default: 0x81

#define CHANNEL_SEL_REGISTER 0x11 // ADC channel select register nr

#define DATA_CFG_REGISTER 0x02
#define OSR_CFG_REGISTER 0x03

#define PIN_CFG_REGISTER 0x05       // AIN/GPIO[7:0]  0b = Channel is configured as analog input. 1b = Channel is configured as GPIO. Default: 0x00
#define GPIO_CFG_REGISTER 0x07      // Configure GPIO[7:0]  0b = GPIO is configured as digital input. 1b = GPIO is configured as digital output. Default: 0x00
#define GPO_DRIVE_CFG_REGISTER 0x09 // Configure GPO[7:0] as open-drain or push-pull. 0b = output is open-drain. 1b = Pushpull driver is used for digital output. Default: 0x00

class EvoLineLeader
{
private:
    int _address;                                    // 7Bit I2C Slave address
    byte _position = 0;                              // ADC0-7
    I2CChannel _channel;                             /**< I2C channel used for communication */
    I2CDevice &i2CDevice = I2CDevice::getInstance(); /**< Reference to the singleton I2CDevice instance */

    void startReadRegister(uint16_t registerAddress);
    void startWriteRegister(uint16_t registerAddress);

public:
    /**
     * @brief Constructor for the EvoLineLeader class.
     * @param channel The I2C channel to use for communication.
     * @param address The I2C address of the EvoLineLeader sensor (default is 0x17).
     */
    EvoLineLeader(I2CChannel channel, int address = 0x17)
    {
        _channel = channel;
        _address = address;
    }

    // begin the Wire with default settings: I2C_SCL = GPIO22, I2C_SDA = GPIO21
    void begin();

    /*read the data from the before selected Analog Input default AIN0
     */
    /**
     * @brief Reads the ADC value from the specified position.
     * @param position The ADC channel position (0-7).
     */
    uint16_t readADC(byte position);

    /**
     * @brief Sets the oversampling ratio for ADC conversion.
     * @param ratio The oversampling ratio (0-7).
     * @details 0b = No averaging
     *          1b = 2 samples
     *          10b = 4 samples
     *          11b = 8 samples
     *          100b = 16 samples
     *          101b = 32 samples
     *          110b = 64 samples
     *          111b = 128 samples
     */
    void setOversamplingRatio(byte ratio);

    /**
     * @brief Gets the current oversampling ratio for ADC conversion.
     * @return The oversampling ratio (0-7).
     */
    byte getOversamplingRatio();
};

#endif