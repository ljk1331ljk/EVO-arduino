#include "EvoTriButton.h"

EvoTriButton::EvoTriButton(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

int EvoTriButton::getButton(int button)
{
    int value = analogRead(_pin);
    if (button != 0)
    {
        if (value >= buttonLows[button] && value <= buttonHighs[button])
            return 1;
        else
            return 0;
    }
    else
        return analogRead(_pin);
}

int EvoTriButton::getButtonPressed()
{
    for (int i = 0; i < 4; i++)
    {
        int reading = analogRead(_pin);
        if (reading >= buttonLows[i] && reading <= buttonHighs[i])
            return i;
    }
    return -1;
}

void EvoTriButton::waitForPress(int button, int debouncems)
{
    while (getButton(button) != 1)
        delay(10);
    delay(debouncems);
}

void EvoTriButton::waitForRelease(int debouncems)
{
    while (getButton(0) != 4095)
        delay(10);
    delay(debouncems);
}

void EvoTriButton::waitForBump(int button, int debouncems)
{
    waitForPress(button, debouncems);
    waitForRelease(debouncems);
}
