/**
 * @file EvoRGBColorSensor.h
 * @brief Class for interfacing with the TCS34725 color sensor using the EvoI2CDevice library.
 */
#ifndef EVO_RGB_COLOR_SENSOR_H
#define EVO_RGB_COLOR_SENSOR_H
#include "../helper/EvoI2CDevice.h"
#include "../helper/AdafruitSensors/Adafruit_TCS34725.h"

/**
 * @class EvoRGBColorSensor
 * @brief Class to interact with the TCS34725 color sensor.
 */
class EvoRGBColorSensor
{
private:
    Adafruit_TCS34725 tcs;                                             /**< Instance of the Adafruit TCS34725 driver */
    I2CChannel _channel;                                               /**< I2C channel used for communication */
    I2CDevice &i2CDevice = I2CDevice::getInstance();                   /**< Reference to the singleton I2CDevice instance */
    uint8_t _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_2_4MS; /**< Integration time for color sensing */
    tcs34725Gain_t _tcs34725Gain = TCS34725_GAIN_16X;                  /**< Gain setting for the sensor */

public:
    /**
     * @brief Constructs an EvoTCS34725 object.
     * @param channel The I2C channel to use.
     */
    EvoRGBColorSensor(I2CChannel channel) : tcs(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X)
    {
        _channel = channel;
    }

    /**
     * @brief Initializes the TCS34725 sensor.
     * @return True if the sensor was successfully initialized, false otherwise.
     */
    bool begin();

    /**
     * @brief Sets the integration time for the sensor.
     * @param it Integration time in milliseconds.
     */
    void setIntegrationTime(uint8_t it);

    /**
     * @brief Sets the gain level for the sensor.
     * @param gain Gain value from the `tcs34725Gain_t` enum.
     * (Default is TCS34725_GAIN_16X).
     * 
     * Gain Values are:
     * - TCS34725_GAIN_1X
     * - TCS34725_GAIN_4X
     * - TCS34725_GAIN_16X
     * - TCS34725_GAIN_60X
     */
    void setGain(tcs34725Gain_t gain);

    /**
     * @brief Retrieves the raw red sensor value.
     * @return Raw red value.
     */
    uint16_t getRawRed();

    /**
     * @brief Retrieves the raw green sensor value.
     * @return Raw green value.
     */
    uint16_t getRawGreen();

    /**
     * @brief Retrieves the raw blue sensor value.
     * @return Raw blue value.
     */
    uint16_t getRawBlue();

    /**
     * @brief Retrieves the raw clear sensor value.
     * @return Raw clear value.
     */
    uint16_t getRawClear();

    /**
     * @brief Retrieves the filtered red value.
     * @return Filtered red value.
     */
    float getRed();

    /**
     * @brief Retrieves the filtered green value.
     * @return Filtered green value.
     */
    float getGreen();

    /**
     * @brief Retrieves the filtered blue value.
     * @return Filtered blue value.
     */
    float getBlue();

    /**
     * @brief Retrieves the RGB color values as floating-point values.
     * @param r Pointer to store the red value.
     * @param g Pointer to store the green value.
     * @param b Pointer to store the blue value.
     */
    void getRGB(float *r, float *g, float *b);

    /**
     * @brief Retrieves the raw RGBC (Red, Green, Blue, Clear) sensor values.
     * @param r Pointer to store the raw red value.
     * @param g Pointer to store the raw green value.
     * @param b Pointer to store the raw blue value.
     * @param c Pointer to store the raw clear value.
     */
    void getRawRGBC(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);

    /**
     * @brief Retrieves the HSV (Hue, Saturation, Value) color values.
     * @param h Pointer to store the hue value (0-360).
     * @param s Pointer to store the saturation value (0-100).
     * @param v Pointer to store the value (0-100).
     */
    void getHSV(float *h, float *s, float *v);
};
#endif
