#include "EvoControllerBase.h"

EvoControllerBase::EvoControllerBase()
    : rgb(1, PIXEL_PIN, NEO_GRBW + NEO_KHZ800),
      display(U8G2_R0, U8X8_PIN_NONE),
      charger()
{
}

void EvoControllerBase::begin()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.begin();
    setFontSize(8);

    charger.begin();
    evoPWMDriver.begin();

    rgb.begin();
    setRGB(0, 0, 0);
}

const char *EvoControllerBase::getBoardName() const
{
    return EvoBoard::NAME;
}

EvoBoardId EvoControllerBase::getBoardId() const
{
    return EvoBoard::ID;
}

float EvoControllerBase::getBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VBAT();
}

float EvoControllerBase::getTopBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLTOP();
}

float EvoControllerBase::getBottomBattery()
{
    charger.wdReset();
    charger.setADC_EN(true);
    charger.pollAllRegs();
    return charger.getADC_VCELLBOT();
}

void EvoControllerBase::playTone(uint frequency, int duration, bool blocking)
{
    if (duration == 0)
    {
        return;
    }

    if (duration == -1)
    {
        tone(BUZZER_PIN, frequency, 0);
        return;
    }

    tone(BUZZER_PIN, frequency, duration);

    if (blocking)
    {
        delay(duration);
        noTone(BUZZER_PIN);
    }
}

void EvoControllerBase::stopTone()
{
    noTone(BUZZER_PIN);
}

void EvoControllerBase::flipDisplayOrientation(bool flip)
{
    display.setFlipMode(flip);
}

void EvoControllerBase::setFontSize(uint8_t size)
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
        break;
    }
}

void EvoControllerBase::clearDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.clearBuffer();
}

void EvoControllerBase::writeToDisplay(
    int value,
    int x,
    int y,
    bool clear,
    bool draw
)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);

    if (clear)
    {
        clearDisplay();
    }

    char text[16];
    itoa(value, text, 10);
    display.drawStr(x, y, text);

    if (draw)
    {
        drawDisplay();
    }
}

void EvoControllerBase::writeToDisplay(
    double value,
    int x,
    int y,
    bool clear,
    bool draw
)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);

    if (clear)
    {
        clearDisplay();
    }

    char text[16];
    dtostrf(value, 1, 2, text);
    display.drawStr(x, y, text);

    if (draw)
    {
        drawDisplay();
    }
}

void EvoControllerBase::writeToDisplay(
    const char *text,
    int x,
    int y,
    bool clear,
    bool draw
)
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);

    if (clear)
    {
        clearDisplay();
    }

    display.drawStr(x, y, text);

    if (draw)
    {
        drawDisplay();
    }
}

void EvoControllerBase::writeLineToDisplay(
    int value,
    int line,
    bool clear,
    bool draw
)
{
    writeToDisplay(value, 0, line * _fontSize, clear, draw);
}

void EvoControllerBase::writeLineToDisplay(
    double value,
    int line,
    bool clear,
    bool draw
)
{
    writeToDisplay(value, 0, line * _fontSize, clear, draw);
}

void EvoControllerBase::writeLineToDisplay(
    const char *text,
    int line,
    bool clear,
    bool draw
)
{
    writeToDisplay(text, 0, line * _fontSize, clear, draw);
}

void EvoControllerBase::drawDisplay()
{
    i2CDevice.selectChannel(SSD1309_CHANNEL);
    display.sendBuffer();
}

void EvoControllerBase::waitForButton()
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }

    while (digitalRead(BUTTON_PIN))
    {
    }

    while (!digitalRead(BUTTON_PIN))
    {
    }
}

void EvoControllerBase::waitForPress(int debounceMs)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }

    while (digitalRead(BUTTON_PIN))
    {
    }

    delay(debounceMs);
}

void EvoControllerBase::waitForRelease(int debounceMs)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }

    while (!digitalRead(BUTTON_PIN))
    {
    }

    delay(debounceMs);
}

void EvoControllerBase::waitForBump(int debounceMs)
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }

    while (digitalRead(BUTTON_PIN))
    {
    }

    delay(debounceMs);

    while (!digitalRead(BUTTON_PIN))
    {
    }

    delay(debounceMs);
}

ButtonState EvoControllerBase::getButton()
{
    if (pinState != BUTTON_STATE)
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        pinState = BUTTON_STATE;
    }

    return static_cast<ButtonState>(digitalRead(BUTTON_PIN));
}

void EvoControllerBase::setRGB(int red, int green, int blue)
{
    pinState = RGB_LED_STATE;
    rgb.setPixelColor(0, rgb.Color(red, green, blue));
    rgb.show();
}

void EvoControllerBase::selectI2CChannel(I2CChannel channel)
{
    i2CDevice.selectChannel(channel);
}

int EvoControllerBase::scanI2CChannel(
    I2CChannel channel,
    uint8_t *addresses,
    int maxAddresses
)
{
    int count = 0;
    selectI2CChannel(channel);

    for (uint8_t address = 1; address < 127; ++address)
    {
        if (
            count < maxAddresses &&
            i2CDevice.isI2CConnected(address)
        )
        {
            addresses[count] = address;
            ++count;
        }
    }

    return count;
}
