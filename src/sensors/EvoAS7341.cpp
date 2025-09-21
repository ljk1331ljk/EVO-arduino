#include "EvoAS7341.h"

bool EvoAS7341::begin() {
   i2CDevice.selectChannel(_channel);
   if (!as7341.begin()) {
      Serial.println(F("[EvoAS7341] Failed to initialize AS7341 sensor."));
      return false;
   }
   Serial.println(F("[EvoAS7341] AS7341 sensor initialized successfully."));
   return true;
}

// Power and Bank Control
void EvoAS7341::powerEnable(bool enable) {
   i2CDevice.selectChannel(_channel);
   as7341.powerEnable(enable);
   Serial.print(F("[EvoAS7341] Power "));
   Serial.println(enable ? F("enabled.") : F("disabled."));
}

bool EvoAS7341::setBank(bool low) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.setBank(low);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to set register bank."));
   }
   return result;
}

// Channel Reading
uint16_t EvoAS7341::readChannel(as7341_adc_channel_t channel) {
   i2CDevice.selectChannel(_channel);
   return as7341.readChannel(channel);
}

uint16_t EvoAS7341::getChannel(as7341_color_channel_t channel) {
   i2CDevice.selectChannel(_channel);
   return as7341.getChannel(channel);
}

bool EvoAS7341::startReading() {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.startReading();
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to start reading."));
   }
   return result;
}

bool EvoAS7341::checkReadingProgress() {
   i2CDevice.selectChannel(_channel);
   return as7341.checkReadingProgress();
}

bool EvoAS7341::getAllChannels(uint16_t *readings_buffer) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.getAllChannels(readings_buffer);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to retrieve all channel readings."));
   }
   return result;
}

bool EvoAS7341::readAllChannels(uint16_t *readings_buffer) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.readAllChannels(readings_buffer);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to read all channels."));
   }
   return result;
}

// Integration Settings
bool EvoAS7341::setIntegration(uint8_t atime, uint16_t astep, as7341_gain_t gain) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.setATIME(atime) && as7341.setASTEP(astep) && as7341.setGain(gain);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to set integration settings."));
   }
   return result;
}

uint8_t EvoAS7341::getATIME() {
   i2CDevice.selectChannel(_channel);
   return as7341.getATIME();
}

uint16_t EvoAS7341::getASTEP() {
   i2CDevice.selectChannel(_channel);
   return as7341.getASTEP();
}

const char* EvoAS7341::getGain() {
   i2CDevice.selectChannel(_channel);
   switch(as7341.getGain()) {
      case AS7341_GAIN_0_5X: return "AS7341_GAIN_0_5X";
      case AS7341_GAIN_1X: return "AS7341_GAIN_1X";
      case AS7341_GAIN_2X: return "AS7341_GAIN_2X";
      case AS7341_GAIN_4X: return "AS7341_GAIN_4X";
      case AS7341_GAIN_8X: return "AS7341_GAIN_8X";
      case AS7341_GAIN_16X: return "AS7341_GAIN_16X";
      case AS7341_GAIN_32X: return "AS7341_GAIN_32X";
      case AS7341_GAIN_64X: return "AS7341_GAIN_64X";
      case AS7341_GAIN_128X: return "AS7341_GAIN_128X";
      case AS7341_GAIN_256X: return "AS7341_GAIN_256X";
      case AS7341_GAIN_512X: return "AS7341_GAIN_512X";
      default: return "UNKNOWN_GAIN"; // Default fallback
   }
}

long EvoAS7341::getTINT() {
   i2CDevice.selectChannel(_channel);
   return as7341.getTINT();
}

// LED Control
bool EvoAS7341::enableLED(bool enable_led) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.enableLED(enable_led);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to enable/disable LED."));
   }
   return result;
}

bool EvoAS7341::setLEDCurrent(uint16_t led_current_ma) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.setLEDCurrent(led_current_ma);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to set LED current."));
   }
   return result;
}

uint16_t EvoAS7341::getLEDCurrent() {
   i2CDevice.selectChannel(_channel);
   return as7341.getLEDCurrent();
}

// Flicker Detection
uint16_t EvoAS7341::detectFlickerHz() {
   i2CDevice.selectChannel(_channel);
   return as7341.detectFlickerHz();
}

float EvoAS7341::toBasicCounts(uint16_t raw) {
   i2CDevice.selectChannel(_channel);
   return as7341.toBasicCounts(raw);
}

void EvoAS7341::normalizeChannels(uint16_t *raw_readings, float *normalized_readings) {
   i2CDevice.selectChannel(_channel);

   float gain = 1.0;
   switch (as7341.getGain()) {
      case AS7341_GAIN_0_5X: gain = 0.5; break;
      case AS7341_GAIN_1X: gain = 1.0; break;
      case AS7341_GAIN_2X: gain = 2.0; break;
      case AS7341_GAIN_4X: gain = 4.0; break;
      case AS7341_GAIN_8X: gain = 8.0; break;
      case AS7341_GAIN_16X: gain = 16.0; break;
      case AS7341_GAIN_32X: gain = 32.0; break;
      case AS7341_GAIN_64X: gain = 64.0; break;
      case AS7341_GAIN_128X: gain = 128.0; break;
      case AS7341_GAIN_256X: gain = 256.0; break;
      case AS7341_GAIN_512X: gain = 512.0; break;
   }

   float integration_time = (as7341.getATIME() + 1) * (as7341.getASTEP() + 1) * 2.78 / 1000.0; // in milliseconds

   // Normalize each channel
   for (int i = 0; i < 12; i++) {
      normalized_readings[i] = raw_readings[i] / (gain * integration_time);
   }
}

bool EvoAS7341::enableSpectralMeasurement(bool enable_measurement) {
   i2CDevice.selectChannel(_channel);
   bool result = as7341.enableSpectralMeasurement(enable_measurement);
   if (!result) {
      Serial.println(F("[EvoAS7341] Failed to enable/disable spectral measurement."));
   }
   return result;
}