/**
 * @file EvoTriButton.h
 * @brief Class for interfacing with the VL53L0X Time-of-Flight distance sensor using the EvoI2CDevice library.
 */
#ifndef EVO_TRIBUTTON_H
#define EVO_TRIBUTTON_H

#include <Arduino.h>

class EvoTriButton
{
private:
    int _pin;
    int buttonLows[4] = {0, 600, 1100, 1800};
    int buttonHighs[4] = {0, 800, 1300, 2100};

public:
    /**
     * @brief Constructor for TriButton.
     * @param GPIOpin The TriButton GPIO pin.
     */
    EvoTriButton(int pin);

    /**
     * @brief Gets the state of the selected button.
     * @param button The button to check. (0 = Raw | 1 = Black | 2 = Red | 3 = Blue).
     * @return The state of the button. (0 = RELEASED | 1 = PRESSED).
     */
    int getButton(int button = 0);

    /**
     * @brief Gets which button is currently pressed.
     * @return The button number that is pressed (0 = None | 1 = Black | 2 = Red | 3 = Blue).
     */
    int getButtonPressed();

    /**
     * @brief Waits for selected button pressed before continuing execution.
     * @param button The button to check. (1 = Black | 2 = Red | 3 = Blue).
     * @param debouncems Delay in milliseconds after button is pressed.
     */
    void waitForPress(int button, int debouncems = 200);

    /**
     * @brief Waits for selected button released before continuing execution.
     * @param debouncems Delay in milliseconds after button is released.
     */
    void waitForRelease(int debouncems = 200);

    /**
     * @brief Waits for selected button pressed and released before continuing execution.
     * @param button The button to check. (1 = Black | 2 = Red | 3 = Blue).
     * @param debouncems Delay in milliseconds after button is pressed and released.
     */
    void waitForBump(int button, int debouncems = 200);
};

#endif