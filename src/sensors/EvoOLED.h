/**
 * @file EvoOLED.h
 * @brief Class for interfacing with the OLED display using the EvoI2CDevice library.
 */
#ifndef EVO_OLED_H
#define EVO_OLED_H

#include "../helper/EvoI2CDevice.h"
#include "../helper/U8g2/U8g2lib.h"

/**
 * @class EvoOLED
 * @brief Class to interact with the OLED display using the EvoI2CDevice library.
 */
class EvoOLED
{
private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled;        /**< U8g2 display object for OLED */
    I2CChannel _channel;                             /**< I2C channel used for communication */
    I2CDevice &i2CDevice = I2CDevice::getInstance(); /**< Reference to the singleton I2CDevice instance */
    /**
     * @brief Size of font for display
     */
    uint8_t _fontSize = 8;

public:
    /**
     * @brief Constructs an EvoOLED object.
     * @param channel The I2C channel to use.
     */
    EvoOLED(I2CChannel channel) : oled(U8G2_R0, U8X8_PIN_NONE)
    {
        _channel = channel;
    }

    /**
     * @brief Initializes the OLED display.
     * @return True if the display was successfully initialized, false otherwise.
     */
    bool begin();

    /**
     * @brief Flips the orientation of the display.
     * @param flip true to flip, false to not flip.
     */

    void flipDisplayOrientation(bool flip = true);

    /**
     * @brief Clears the OLED display.
     */
    void clearDisplay();

    /**
     * @brief Sets the font size for the display.
     * @param size The font size to set.
     */
    void setFontSize(uint8_t size);

    /**
     * @brief Writes an integer value to the display at a specific position.
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

    /**
     * @brief Writes an integer value to the display on a specific line.
     * @param value The integer value to display.
     * @param line The line number (0-7).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */
    void writeLineToDisplay(int value, int line, bool clear = false, bool draw = false);

    /**
     * @brief Writes a floating-point number to the display on a specific line.
     * @param f The floating-point number to display.
     * @param line The line number (0-7).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */

    void writeLineToDisplay(double f, int line, bool clear = false, bool draw = false);

    /**
     * @brief Writes a string to the display on a specific line.
     * @param c The string to display.
     * @param line The line number (0-7).
     * @param clear Whether to clear the screen before drawing.
     * @param draw Whether to immediately draw the screen.
     */
    void writeLineToDisplay(const char *c, int line, bool clear = false, bool draw = false);

    /**
     * @brief Refreshes the display by rendering the current buffer.
     */
    void drawDisplay();

    /**
     * @brief Draws a pixel on the display at the specified coordinates.
     * @param x X-coordinate of the pixel (0-127).
     * @param y Y-coordinate of the pixel (0-63).
     * @param clear Whether to clear the pixel (true) or draw it (false).
     * @param draw Whether to immediately draw the screen after setting the pixel.
     */
    void drawPixel(int x, int y, bool clear = false, bool draw = false);

    /**
     * @brief Draws a line between two points on the display.
     * @param x0 X-coordinate of the start point (0-127).
     * @param y0 Y-coordinate of the start point (0-63).
     * @param x1 X-coordinate of the end point (0-127).
     * @param y1 Y-coordinate of the end point (0-63).
     * @param clear Whether to clear the line (true) or draw it (false).
     * @param draw Whether to immediately draw the screen after setting the line.
     */
    void drawLine(int x0, int y0, int x1, int y1, bool clear = false, bool draw = false);

    /**
     * @brief Draws a rectangle on the display.
     * @param x X-coordinate of the top-left corner (0-127).
     * @param y Y-coordinate of the top-left corner (0-63).
     * @param w Width of the rectangle (1-128).
     * @param h Height of the rectangle (1-64).
     * @param fill Whether to fill the rectangle (true) or draw only the outline (false).
     * @param clear Whether to clear the rectangle (true) or draw it (false).
     * @param draw Whether to immediately draw the screen after setting the rectangle.
     */
    void drawRect(int x, int y, int w, int h, bool fill = false, bool clear = false, bool draw = false);

    /**
     * @brief Draws a circle on the display.
     * @param x X-coordinate of the center of the circle (0-127).
     * @param y Y-coordinate of the center of the circle (0-63).
     * @param r Radius of the circle (1-64).
     * @param fill Whether to fill the circle (true) or draw only the outline (false).
     * @param clear Whether to clear the circle (true) or draw it (false).
     * @param draw Whether to immediately draw the screen after setting the circle.
     */
    void drawCircle(int x, int y, int r, bool fill = false, bool clear = false, bool draw = false);

    /**
     * @brief Draws a triangle on the display.
     * @param x0 X-coordinate of the first vertex (0-127).
     * @param y0 Y-coordinate of the first vertex (0-63).
     * @param x1 X-coordinate of the second vertex (0-127).
     * @param y1 Y-coordinate of the second vertex (0-63).
     * @param x2 X-coordinate of the third vertex (0-127).
     * @param y2 Y-coordinate of the third vertex (0-63).
     * @param clear Whether to clear the triangle (true) or draw it (false).
     * @param draw Whether to immediately draw the screen after setting the triangle.
     */
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool clear = false, bool draw = false);
};
#endif