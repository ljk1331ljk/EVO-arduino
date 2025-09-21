/**
 * @file EvoAS7341.h
 * @brief Class for interfacing with the AS7341 spectral sensor using the EvoI2CDevice library.
 */
#ifndef EVO_AS7341_H
#define EVO_AS7341_H

#include "../helper/EvoI2CDevice.h"
#include <Adafruit_AS7341.h>

/**
 * @class EvoAS7341
 * @brief Class to interact with the AS7341 spectral sensor.
 */
class EvoAS7341 {
private:
   Adafruit_AS7341 as7341;  ///< Instance of third-party sensor class
   I2CChannel _channel;     ///< I2C multiplexer channel
   I2CDevice &i2CDevice = I2CDevice::getInstance(); ///< Singleton multiplexer manager

public:
   /**
    * @brief Constructs an EvoAS7341 object.
    * @param channel The I2C channel to use.
    */
   EvoAS7341(I2CChannel channel) : as7341() {
      _channel = channel;
   }

   /**
    * @brief Initializes the AS7341 sensor.
    * @return True if initialization is successful, false otherwise.
    */
   bool begin();

   /**
    * @brief Enables or disables the power to the sensor.
    * @param enable True to enable power, false to disable.
    */
   void powerEnable(bool enable);

   /**
    * @brief Sets the register bank of the sensor.
    * @param low True for low bank, false for high bank.
    * @return True if successful, false otherwise.
    */
   bool setBank(bool low);

   /**
    * @brief Reads data from a specific ADC channel.
    * @param channel The ADC channel to read.
    * @return The raw data from the channel.
    */
   uint16_t readChannel(as7341_adc_channel_t channel);

   /**
    * @brief Gets the data from a specific color channel.
    * @param channel The color channel to read.
    * @return The raw data from the channel.
    */
   uint16_t getChannel(as7341_color_channel_t channel);

   /**
    * @brief Starts the reading process for all channels.
    * @return True if successful, false otherwise.
    */
   bool startReading();

   /**
    * @brief Checks the progress of the reading process.
    * @return True if reading is complete, false otherwise.
    */
   bool checkReadingProgress();

   /**
    * @brief Retrieves all channel readings into a buffer.
    * @param readings_buffer Pointer to the buffer to store readings.
    * @return True if successful, false otherwise.
    */
   bool getAllChannels(uint16_t *readings_buffer);

   /**
    * @brief Converts raw ADC values to basic counts.
    * @param raw The raw ADC value.
    * @return The basic counts.
    */
   float toBasicCounts(uint16_t raw);

   /**
    * @brief Normalizes the raw channel readings based on gain and integration time.
    * @param raw_readings Pointer to an array of raw readings (12 elements).
    * @param normalized_readings Pointer to an array to store normalized readings (12 elements).
    */
   void normalizeChannels(uint16_t *raw_readings, float *normalized_readings);

   /**
    * @brief Sets the integration settings for the sensor.
    * @param atime Integration time step count.
    * @param astep Integration time step size.
    * @param gain ADC gain multiplier.
    * @return True if successful, false otherwise.
    */
   bool setIntegration(uint8_t atime, uint16_t astep, as7341_gain_t gain);

   /**
    * @brief Gets the current integration settings.
    * @return The current ATIME value.
    */
   uint8_t getATIME();

   /**
   * @brief Gets the current integration settings.
   * @return The current ASTEP value.
   */
   uint16_t getASTEP();

   /** 
    * @brief Gets the current gain setting.
    * @return The current gain setting.
    */
   const char* getGain();

   /**
    * @brief Gets the current integration time in milliseconds.
    * @return The integration time in milliseconds.
    */
   long getTINT();

   /**
    * @brief Enables or disables the onboard LED.
    * @param enable_led True to enable the LED, false to disable.
    * @return True if successful, false otherwise.
    */
   bool enableLED(bool enable_led);

   /**
    * @brief Sets the current limit for the onboard LED.
    * @param led_current_ma The current limit in milliamps.
    * @return True if successful, false otherwise.
    */
   bool setLEDCurrent(uint16_t led_current_ma);

   /**
    * @brief Gets the current limit for the onboard LED.
    * @return The current limit in milliamps.
    */
   uint16_t getLEDCurrent();

   /**
    * @brief Enables or disables spectral measurement.
    * @param enable_measurement True to enable, false to disable.
    * @return True if successful, false otherwise.
    */
   bool enableSpectralMeasurement(bool enable_measurement);

   /**
    * @brief Detects the flicker frequency of light.
    * @return The detected flicker frequency in Hz.
    */
   uint16_t detectFlickerHz();

   /**
    * @brief Reads all channels and stores the results in the provided buffer.
    * @param readings_buffer Pointer to the buffer to store readings.
    * @return True if successful, false otherwise.
    */
   bool readAllChannels(uint16_t *readings_buffer);
};

#endif