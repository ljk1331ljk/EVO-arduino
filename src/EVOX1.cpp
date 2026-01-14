#include <Evo.h>

void EVOX1::begin()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.begin();
    this->setFontSize(8);

    charger.begin();
    evoPWMDriver.begin();

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

void EVOX1::playTone(uint frequency, int duration, bool blocking)
{
    if (duration == 0)
    {
        return;
    }
    else if (duration == -1)
    {
        tone(BUZZER_PIN, frequency, 0);
        return;
    }
    else
    {
        tone(BUZZER_PIN, frequency, duration);
        if (blocking)
        {
            delay(duration);
            noTone(BUZZER_PIN);
        }
    }
}

void EVOX1::stopTone()
{
    noTone(BUZZER_PIN);
}

void EVOX1::flipDisplayOrientation(bool flip)
{
    display.setFlipMode(flip);
}

void EVOX1::setFontSize(uint8_t size)
{
    _fontSize = size;
    display.setFontPosTop();
    switch (size)
    {
    case 4:
        display.setFont(u8g2_font_minimal3x3_tu);
        break;
    case 5:
        display.setFont(u8g2_font_u8glib_4_tf);
        break;
    case 6:
        display.setFont(u8g2_font_tiny5_tf);
        break;
    case 7:
        display.setFont(u8g2_font_5x7_tf);
        break;
    case 8:
        display.setFont(u8g2_font_6x10_tf);
        break;
    case 9:
        display.setFont(u8g2_font_profont12_tf);
        break;
    case 10:
        display.setFont(u8g2_font_6x13_tf);
        break;
    default:
        display.setFont(u8g2_font_5x7_tf);
    }
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

void EVOX1::writeToDisplay(double f, int x, int y, bool clear, bool draw)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    if (clear)
    {
        this->clearDisplay();
    }
    char myString[16];
    dtostrf(f, 1, 2, myString);
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

void EVOX1::writeLineToDisplay(int value, int line, bool clear, bool draw)
{
    writeToDisplay(value, 0, line * _fontSize, clear, draw);
}

void EVOX1::writeLineToDisplay(double f, int line, bool clear, bool draw)
{
    writeToDisplay(f, 0, line * _fontSize, clear, draw);
}

void EVOX1::writeLineToDisplay(const char *c, int line, bool clear, bool draw)
{
    writeToDisplay(c, 0, line * _fontSize, clear, draw);
}

void EVOX1::drawDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.sendBuffer();
}

void EVOX1::waitForButton()
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }
    while (digitalRead(BUTTON_PIN))
        ;
    while (!digitalRead(BUTTON_PIN))
        ;
}

void EVOX1::waitForPress(int debouncems)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }
    while (digitalRead(BUTTON_PIN))
        ;
    delay(debouncems);
}

void EVOX1::waitForRelease(int debouncems)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }
    while (!digitalRead(BUTTON_PIN))
        ;
    delay(debouncems);
}

void EVOX1::waitForBump(int debouncems)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }
    while (digitalRead(BUTTON_PIN))
        ;
    delay(debouncems);
    while (!digitalRead(BUTTON_PIN))
        ;
    delay(debouncems);
}

ButtonState EVOX1::getButton()
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }
    return static_cast<ButtonState>(digitalRead(BUTTON_PIN));
}

void EVOX1::setRGB(int r, int g, int b)
{
    this->pinState = RGB_LED_STATE;
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
        if ((count < maxAddresses) &&
            i2CDevice.isI2CConnected(address))
        {
            addresses[count] = address;
            count++;
        }
    }
    return count;
}