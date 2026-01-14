
#include "EvoLineLeader.h"

void startReadRegister(uint16_t registerAddress)
{
    Wire.beginTransmission(registerAddress); // write to Address
    Wire.write(0b000010000);                 // reading data to I2C device address
    Wire.write(PIN_CFG_REGISTER);            // register address
    Wire.endTransmission();                  // end Transmission I2C
}

void EvoLineLeader::begin()
{
    i2CDevice.selectChannel(_channel);
}

uint16_t EvoLineLeader::readADC(byte position)
{
    i2CDevice.selectChannel(_channel);

    if (_position != position)
    {
        Wire.beginTransmission(_address); // write to Address
        Wire.write(0b00001000);           // writing data to I2C device address
        Wire.write(CHANNEL_SEL_REGISTER); // register address
        Wire.write(0b0000 + (_position)); // register data
        Wire.endTransmission();
        _position = position;
    }

    uint16_t output;

    Wire.requestFrom(_address, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = (Wire.read() << 8 | Wire.read()) >> 4;
    }

    return output;
}

void EvoLineLeader::setOversamplingRatio(byte ratio)
{
    i2CDevice.selectChannel(_channel);
    Wire.beginTransmission(_address); // write to Address
    Wire.write(0b00001000);           // writing data to I2C device address
    Wire.write(OSR_CFG_REGISTER);     // register address
    Wire.write(0b00000 + ratio);      // register data
    Wire.endTransmission();
}

byte EvoLineLeader::getOversamplingRatio()
{
    i2CDevice.selectChannel(_channel);
    byte data;
    Wire.beginTransmission(_address);
    Wire.write(0b00010000);       // read Register
    Wire.write(OSR_CFG_REGISTER); // Send the register address to read from
    Wire.endTransmission(false);
    Wire.requestFrom(_address, 1);
    if (Wire.available() >= 1)
    {
        data = Wire.read(); // Read the received data
    }
    Wire.endTransmission(); // End the communication with the device
    return data;
}
