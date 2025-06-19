/**
 * @file EVOX1.h
 * @brief Singleton class for managing the EVOX1 controller's peripherals.
 */

#ifndef EVOX1_H
#define EVOX1_H
#include <Arduino.h>
#include <helper/X1pins.h>
#include <helper/Tones.h>
#include <helper/EvoI2CDevice.h>
#include <helper/EvoPWMDriver.h>
#include <helper/EvoBQ25887.h>
#include <Adafruit_NeoPixel.h>
#include <helper/U8g2/U8g2lib.h>

/**
 * @enum ButtonState
 * @brief Enumeration of different button states.
 */
enum ButtonState
{
    PRESSED,
    RELEASED,
};

/**
 * @enum PinState
 * @brief Enumeration of the state of multiplexed button/rgb led pin
 */
enum PinState
{
    BUTTON_STATE,
    RGB_LED_STATE
};

/**
 * @class EVOX1
 * @brief Manages the EVOX1 controller, handling display, battery, I2C, buttons, and RGB functions.
 *
 * This class implements a singleton pattern to ensure only one instance is created.
 */
class EVOX1
{
private:
    /**
     * @brief RGB LED instance using Adafruit NeoPixel.
     */
    Adafruit_NeoPixel rgb;

    /**
     * @brief Size of font for display
     */
    uint8_t _fontSize = 8;

    /**
     * @brief Initial of pin state of the multiplexed pin
     */
    PinState pinState = RGB_LED_STATE;

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    EVOX1(const EVOX1 &) = delete;

    /**
     * @brief Deleted assignment operator to prevent assignment.
     */
    EVOX1 &operator=(const EVOX1 &) = delete;

    /**
     * @brief Singleton instance of I2CDevice.
     */
    I2CDevice &i2CDevice = I2CDevice::getInstance();

    /**
     * @brief Singleton instance of EvoPWMDriver.
     */
    EvoPWMDriver &evoPWMDriver = EvoPWMDriver::getInstance();

public:
    /**
     * @brief Gets the singleton instance of EVOX1.
     */
    EVOX1() : display(U8G2_R0, U8X8_PIN_NONE),
              rgb(1, PIXEL_PIN, NEO_GRBW + NEO_KHZ800)
    {
    }

    /**
     * @brief OLED display instance using U8G2 library.
     */
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

    /**
     * @brief Gets the singleton instance of EVOX1.
     * @return Reference to the singleton instance.
     */
    static EVOX1 &getInstance()
    {
        static EVOX1 instance;
        return instance;
    }

    /**
     * @brief Battery charger instance.
     */
    EvoBQ25887 charger = EvoBQ25887();

    /**
     * @brief Initializes the EVOX1 board and its peripherals.
     */
    void begin();

    /**
     * @brief Selects an I2C channel on the multiplexer.
     * @param channel The I2C channel to select.
     */
    void selectI2CChannel(I2CChannel channel);

    /**
     * @brief Scans for I2C devices on a specific channel.
     * @param channel The I2C channel to scan.
     * @param addresses Pointer to store detected device addresses.
     * @param maxAddresses Maximum number of addresses that can be stored.
     * @return The number of devices found.
     */
    int scanI2CChannel(I2CChannel channel, uint8_t *addresses, int maxAddresses);

    // === Battery Functions ===

    /**
     * @brief Gets the voltage of the top battery.
     * @return The voltage of the top battery in volts.
     */
    float getTopBattery();

    /**
     * @brief Gets the voltage of the bottom battery.
     * @return The voltage of the bottom battery in volts.
     */
    float getBottomBattery();

    /**
     * @brief Gets the combined battery voltage.
     * @return The total battery voltage in volts.
     */
    float getBattery();

    // === Display Functions ===

    /**
     * @brief Flips the orientation of the display
     * @param flip true to flip, false to not flip.
     */
    void flipDisplayOrientation(bool flip = true);

    /**
     * @brief Clears the OLED display.
     */
    void clearDisplay();

    /**
     * @brief Writes an integer to the display at a specific position.
     * @param value The integer value to display.
     * @param x X-coordinate position (0-128).
     * @param y Y-coordinate position (0-64).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */
    void writeToDisplay(int value, int x, int y, bool clear = false, bool draw = false);

    /**
     * @brief Writes a floating-point number to the display at a specific position.
     * @param f The floating-point number to display.
     * @param x X-coordinate position (0-128).
     * @param y Y-coordinate position (0-64).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */
    void writeToDisplay(double f, int x, int y, bool clear = false, bool draw = false);

    /**
     * @brief Writes a string to the display at a specific position.
     * @param c The string to display.
     * @param x X-coordinate position (0-128).
     * @param y Y-coordinate position (0-64).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */
    void writeToDisplay(const char *c, int x, int y, bool clear = false, bool draw = false);

    void writeLineToDisplay(int value, int line, bool clear = false, bool draw = false);

    void writeLineToDisplay(double f, int line, bool clear = false, bool draw = false);

    void writeLineToDisplay(const char *c, int line, bool clear = false, bool draw = false);

    /**
     * @brief Refreshes the display by rendering the current buffer.
     */
    void drawDisplay();

    /**
     * @brief Sets the font size for the display.
     * @param size The font size.
     */
    void setFontSize(uint8_t size);

    // === Button Functions ===

    /**
     * @brief Waits for a button press and release before continuing execution. (To be deprecated, use waitForBumped(int debouncems))
     */
    void waitForButton();

    /**
     * @brief Waits for a button press before continuing execution.
     * @param debouncems delay in milliseconds after button is pressed.
     */
    void waitForPress(int debouncems = 0);

    /**
     * @brief Waits for a button released before continuing execution.
     * @param debouncems delay in milliseconds after button is released.
     */
    void waitForRelease(int debouncems = 0);

    /**
     * @brief Waits for a button press and release before continuing execution.
     * @param debouncems delay in milliseconds after button is pressed and button is released.
     */
    void waitForBump(int debouncems = 0);

    /**
     * @brief Gets the state of the button.
     * @return The state of the button. PRESSED or RELEASED.
     */
    ButtonState getButton();

    // === Buzzer Functions ===

    /**
     * @brief Plays a tone on the buzzer.
     * @param frequency The frequency of the tone in Hz.
     * @param duration The duration of the tone in milliseconds. If -1, plays indefinitely until stopped.
     * @note If duration is -1, you must call stopTone() to stop the tone.
     * @see stopTone()
     */
    void playTone(uint frequency, int duration = -1, bool blocking = true);

    /**
     * @brief Stops the currently playing tone on the buzzer.
     */
    void stopTone();

    // === RGB LED Functions ===

    /**
     * @brief Sets the color of the RGB LED.
     * @param r Red intensity (0-255).
     * @param g Green intensity (0-255).
     * @param b Blue intensity (0-255).
     */
    void setRGB(int r, int g, int b);
};

#endif // EVOX1_H