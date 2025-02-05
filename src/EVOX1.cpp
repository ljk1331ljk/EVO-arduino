/**
 * @file EVOX1.cpp
 *
 * @mainpage Doxygen Example Project
 *
 * @section description Description
 * An example sketch demonstrating how to use Doxygen style comments for
 * generating source code documentation with Doxygen.
 *
 * @section circuit Circuit
 * - Red LED connected to pin D2.
 * - Momentary push button connected to pin D3.
 *
 * @section libraries Libraries
 * - Arduino_LSM6DS3 (https://github.com/arduino-libraries/Arduino_LSM6DS3)
 *   - Interacts with on-board IMU.
 *
 * @section notes Notes
 * - Comments are Doxygen compatible.
 *
 * @section todo TODO
 * - Don't use Doxygen style formatting inside the body of a function.
 *
 * @section author Author
 * - Created by John Woolsey on 03/12/2020.
 * - Modified by John Woolsey on 03/16/2020.
 *
 * Copyright (c) 2025 TribalStudioz.  All rights reserved.
 */

#include <EVO.h>

void EVOX1::begin()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.begin();
    this->setFontSize(7);
    charger.begin();
    rgb.begin();
    setRGB(0, 0, 0);
}

float EVOX1::getBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VBAT();
}

float EVOX1::getTopBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLTOP();
}

float EVOX1::getBottomBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLBOT();
}

void EVOX1::playTone(uint frequency, int duration)
{
    tone(BUZZER_PIN, frequency, duration);
}

void EVOX1::clearDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.clearBuffer();
}

void EVOX1::writeToDisplay(int value, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    if (clear)
    {
        this->clearDisplay();
    }
    char myString[16];
    itoa(value, myString, 10);
    display.drawStr(x, y, myString);
    if (draw)
    {
        this->drawDisplay();
    }
}

void EVOX1::setFontSize(uint8_t size)
{
    display.setFontPosTop();
    switch (size)
    {
    case 3:
        display.setFont(u8g2_font_minimal3x3_tu);
        break;
    case 4:
        display.setFont(u8g2_font_u8glib_4_tf);
        break;
    case 5:
        display.setFont(u8g2_font_tiny5_tf);
        break;
    case 6:
        display.setFont(u8g2_font_5x7_tf);
        break;
    case 7:
        display.setFont(u8g2_font_6x10_tf);
        break;
    case 8:
        display.setFont(u8g2_font_profont12_tf);
        break;
    case 9:
        display.setFont(u8g2_font_6x13_tf);
        break;
    case 10:
        display.setFont(u8g2_font_7x14_tf);
        break;
    default:
        display.setFont(u8g2_font_5x7_tf);
    }
}

void EVOX1::writeToDisplay(double f, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    if (clear)
    {
        this->clearDisplay();
    }
    char myString[16];
    dtostrf(f, 6, 2, myString);
    display.drawStr(x, y, myString);
    if (draw)
    {
        this->drawDisplay();
    }
}

void EVOX1::writeToDisplay(const char *c, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    if (clear)
    {
        this->clearDisplay();
    }
    display.drawStr(x, y, c);
    if (draw)
    {
        this->drawDisplay();
    }
}

void EVOX1::waitForButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    while (digitalRead(BUTTON_PIN))
        ;
    while (!digitalRead(BUTTON_PIN))
        ;
}

void EVOX1::drawDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.sendBuffer();
}

void EVOX1::setRGB(int r, int g, int b)
{
    rgb.setPixelColor(0, rgb.Color(r, g, b));
    rgb.show();
}

void EVOX1::selectI2CChannel(I2CChannel channel)
{
    i2CDevice.selectChannel(channel);
}

int EVOX1::scanI2CChannel(I2CChannel channel, uint8_t *addresses, int maxAddresses = 5)
{
    int count = 0;
    selectI2CChannel(channel);

    for (uint8_t address = 1; address < 127; ++address)
    {
        if (count < maxAddresses)
            i2CDevice.isI2CConnected(address);
        {
            addresses[count] = address;
            count++;
        }
    }
    return count;
}