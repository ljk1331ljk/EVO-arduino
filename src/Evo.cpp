#include <Evo.h>

void EVO::begin()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.begin();
    this->setFontSize(7);
    charger.begin();
    rgb.begin();
    setRGB(0, 0, 0);
}

float EVO::getBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VBAT();
}
float EVO::getTopBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLTOP();
}

float EVO::getBottomBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLBOT();
}

void EVO::playTone(uint frequency, int duration)
{
    pinMode(BUZZER_PIN, OUTPUT);
    tone(BUZZER_PIN, frequency, duration);
}

void EVO::clearDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.clearBuffer();
}

void EVO::writeToDisplay(int value, int x, int y, bool clear, bool draw)
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
void EVO::setFontSize(uint8_t size)
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

void EVO::writeToDisplay(double f, int x, int y, bool clear, bool draw)
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
void EVO::writeToDisplay(const char *c, int x, int y, bool clear, bool draw)
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

void EVO::waitForButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    while (digitalRead(BUTTON_PIN))
        ;
}

void EVO::drawDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.sendBuffer();
}

void EVO::setRGB(int r, int g, int b)
{
    rgb.setPixelColor(0, rgb.Color(r, g, b));
    rgb.show();
}

void EVO::selectI2CChannel(I2CChannel channel)
{
    i2CDevice.selectChannel(channel);
}