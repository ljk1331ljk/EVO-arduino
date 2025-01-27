#ifndef EVO_H
#define EVO_H
// #define SH110X_NO_SPLASH
#include <Arduino.h>
#include <helper/X1pins.h>
#include <helper/Tones.h>
#include <helper/EvoI2CDevice.h>
#include <helper/EvoBQ25887.h>
#include <Adafruit_NeoPixel.h>
#include <helper/U8g2/U8g2lib.h>

class EVO
{
private:
  // Instantiate Display
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

  Adafruit_NeoPixel rgb;

  // Delete the copy constructor and assignment operator
  EVO(const EVO &) = delete;
  EVO &operator=(const EVO &) = delete;

  // Instantiate I2CDevice
  I2CDevice &i2CDevice = I2CDevice::getInstance();

public:
  EVO() : display(U8G2_R0, U8X8_PIN_NONE), rgb(1, PIXEL_PIN, NEO_GRBW + NEO_KHZ800)
  {
  }

  static EVO &getInstance()
  {
    static EVO instance;
    return instance;
  }

  EvoBQ25887 charger = EvoBQ25887();

  void begin();

  void selectI2CChannel(I2CChannel channel);

  // Battery charger functions
  float getTopBattery();
  float getBottomBattery();
  float getBattery();

  // Pherperial functions

  // Display functions
  void clearDisplay();
  void writeToDisplay(int value, int x, int y, bool clear = false, bool draw = false);
  void writeToDisplay(double f, int x, int y, bool clear = false, bool draw = false);
  void writeToDisplay(const char *c, int x, int y, bool clear = false, bool draw = false);
  void drawDisplay();
  void setFontSize(uint8_t size);

  // Onboard button functions
  void waitForButton();

  // Buzzer function
  void playTone(uint frequency, int duration);

  void setRGB(int r, int g, int b);
};

#endif