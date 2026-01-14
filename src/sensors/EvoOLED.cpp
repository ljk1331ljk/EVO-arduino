#include "EvoOLED.h"

bool EvoOLED::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!oled.begin())
    {
        return false;
    }
    this->setFontSize(8);
    return true;
}

void EvoOLED::clearDisplay()
{
    i2CDevice.selectChannel(_channel);
    oled.clearBuffer();
    oled.sendBuffer();
}

void EvoOLED::setFontSize(uint8_t size)
{
    _fontSize = size;
    oled.setFontPosTop();
    switch (size)
    {
    case 4:
        oled.setFont(u8g2_font_minimal3x3_tu);
        break;
    case 5:
        oled.setFont(u8g2_font_u8glib_4_tf);
        break;
    case 6:
        oled.setFont(u8g2_font_tiny5_tf);
        break;
    case 7:
        oled.setFont(u8g2_font_5x7_tf);
        break;
    case 8:
        oled.setFont(u8g2_font_6x10_tf);
        break;
    case 9:
        oled.setFont(u8g2_font_profont12_tf);
        break;
    case 10:
        oled.setFont(u8g2_font_6x13_tf);
        break;
    default:
        oled.setFont(u8g2_font_5x7_tf);
    }
}

void EvoOLED::writeToDisplay(int value, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.setCursor(x, y);
    oled.print(value);
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::writeToDisplay(double f, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.setCursor(x, y);
    oled.print(f);
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::writeToDisplay(const char *c, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.setCursor(x, y);
    oled.print(c);
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::writeLineToDisplay(int value, int line, bool clear, bool draw)
{
    writeToDisplay(value, 0, line * _fontSize, clear, draw);
}

void EvoOLED::writeLineToDisplay(double f, int line, bool clear, bool draw)
{
    writeToDisplay(f, 0, line * _fontSize, clear, draw);
}

void EvoOLED::writeLineToDisplay(const char *c, int line, bool clear, bool draw)
{

    writeToDisplay(c, 0, line * _fontSize, clear, draw);
}
void EvoOLED::drawDisplay()
{
    i2CDevice.selectChannel(_channel);
    oled.sendBuffer();
}

void EvoOLED::flipDisplayOrientation(bool flip)
{
    i2CDevice.selectChannel(_channel);
    oled.setFlipMode(flip);
}

void EvoOLED::drawPixel(int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.drawPixel(x, y);
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::drawLine(int x0, int y0, int x1, int y1, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.drawLine(x0, y0, x1, y1);
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::drawRect(int x, int y, int w, int h, bool fill, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    if (fill)
    {
        oled.drawBox(x, y, w, h);
    }
    else
    {
        oled.drawFrame(x, y, w, h);
    }
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::drawCircle(int x, int y, int radius, bool fill, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    if (fill)
    {
        oled.drawDisc(x, y, radius);
    }
    else
    {
        oled.drawCircle(x, y, radius);
    }
    if (draw)
        oled.sendBuffer();
}

void EvoOLED::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool clear, bool draw)
{
    i2CDevice.selectChannel(_channel);
    if (clear)
        oled.clearBuffer();
    oled.drawTriangle(x0, y0, x1, y1, x2, y2);
    if (draw)
        oled.sendBuffer();
}
