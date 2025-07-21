Connecting 3rd-Party I2C Devices
================================

This guide is for those who wish to interface 3rd-party I2C devices. As EVOX1 is made to be open source, you are not limited to the sensors and motors that are provided by the EVOX1. 

The Arduino library for these devices will work with the EVOX1, but you will need to make some modifications to the library code to make it compatible with the EVOX1.

.. note::

   This guide is for advanced users who are familiar with Arduino programming and electronics. If you are a beginner, we recommend that you start with the official sensors and motors provided by the EVOX1.

Understanding I2C Communication
-------------------------------

I2C lets multiple devices share just two wires: SDA (Serial Data) and SCL (Serial Clock). Each device has an address, like a name. The host (like EVOX1) talks to one device at a time by calling its address. Only the matching device responds, the rest stay silent.

However, some devices can’t change their address. If you connect two devices with the same address, they clash and the system fails.

Instead of connecting all devices directly, we use an I2C multiplexer. It works like a switch, letting only one device at a time appear on the I2C bus. This avoids address conflicts without needing extra pins or soldering.

Now, before talking to a device, we first tell the multiplexer which channel to activate. It adds one extra I2C step, but makes everything work smoothly even with devices that share the same address.

Making Changes to the code 
--------------------------

Folder Structure
^^^^^^^^^^^^^^^^

.. code-block:: text

   /src
   ├── sensors/
   │    ├── EvoSensorName.h
   │    └── EvoSensorName.cpp
   └── main.ino

Step 1: Header File
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp
   :linenos:

   #ifndef EVO_SENSORNAME_H
   #define EVO_SENSORNAME_H

   #include "../helper/EvoI2CDevice.h"
   #include <ThirdPartySensorLibrary.h>  // Replace with the actual sensor header

   class EvoSensorName {
   private:
      ThirdPartySensor sensor;   // Instance of third-party sensor class
      I2CChannel _channel;       // I2C multiplexer channel
      I2CDevice &i2CDevice = I2CDevice::getInstance(); // Singleton multiplexer manager

   public:
      EvoSensorName(I2CChannel channel) : sensor() {
         _channel = channel;
      }

      void begin();
      float readValue();  // Replace with actual sensor methods
   };

   #endif

Step 2: Source File
^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp
   :emphasize-lines: 12
   :linenos:

   #include "EvoSensorName.h"

   void EvoSensorName::begin() {
      i2CDevice.selectChannel(_channel);
      if (!sensor.begin()) {
         Serial.println(F("Sensor failed to start"));
      }
   }

   // Add this line to All the functions in the library
   float EvoSensorName::readValue() {
      i2CDevice.selectChannel(_channel);
      return sensor.read();  // Replace with actual read function
   }

Step 3: Add to your Main code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: cpp
   :linenos:

   #include "EvoSensorName.h"

   EvoSensorName sensor0(i2c_port);
   EvoSensorName sensor1(i2c_port);

   void setup() {
      Serial.begin(115200);
      sensor0.begin();
      sensor1.begin();
   }

   void loop() {
      float val0 = sensor0.readValue();
      float val1 = sensor1.readValue();

      Serial.print("Sensor 0: "); Serial.println(val0);
      Serial.print("Sensor 1: "); Serial.println(val1);
      delay(500);
   }