Over-The-Air (OTA) Download
=========================

The Evo library has built in Over-The-Air support based on `ArduinoOTA <https://docs.arduino.cc/arduino-cloud/features/ota-getting-started/>`_. OTA update is supported in both Arduino IDE 2 and PlatformIO.
It uses the Wi-Fi feature on the Evo and can work in Station mode (STA_MODE) and Access Point mode (AP_MODE). In STA_MODE, the Evo connects to a Wi-Fi access point that the computer is also connected to. 
In AP_MODE, the Evo creates an access point and the computer is able to connect to it. 


OTA Usage
----------------

To be able to perform OTA the following requirements must be met.

1. It must not be in a program crashed state.
2. It also must not be in any loop without delay being called at some point in the code.
3. The Wi-Fi connection on the EVO must not be used for anything else.
4. OTA must be initialised via code and have been downloaded into the Evo via a wired connection.
5. If station mode is used, the Wi-Fi network needs to be 2.4GHz.

The following program shows how the OTA feature is enabled. The OTA feature will run in the background while other functions still function.


.. code-block:: cpp
   :linenos:

   #include <Evo.h>

   EVOX1 evo;
   // If STA_MODE is used
   OTAHandler ota(STA_MODE, "EvoX1-OTA", "NetworkSSID", "Networkpassword", "ArduinoOTAPassword");

   //If AP_MODE is used
   //OTAHandler ota(AP_MODE, "EvoX1-OTA", "NetworkSSID", "Networkpassword", "ArduinoOTAPassword");

   void setup()
   {
      evo.begin();
      ota.begin();
      
   }

   void loop(){
      delay(1)
   }

If AP_MODE is selected, the Evo will generate a 2.4GHz access point where the SSID is given by ``NetworkSSID`` and password is ``Networkpassword``. Connect to that network to allow OTA update.


OTA update on Arduino IDE 2
----------------------------

When the Evo is running OTA and the computer is connected to it via Wi-Fi, you should see the device on select board.

.. figure:: /_static/images/ArduinoIDEOTADevice.png
   :alt: Arduino OTA device selection
   :width: 100%
   :align: center

When you download code to it for the first time, it will prompt you for the ``ArduinoOTAPassword``.

.. figure:: /_static/images/ArduinoIDEOTAPassword.png
   :alt: Arduino OTA password
   :width: 100%
   :align: center

Password is required for the first time and no longer reguired subsequently.

OTA update on PlatformIO
----------------------------

To download on PlatformIO, the ``platform.ini`` needs to be configured correctly. Add the following into ``platform.ini``. 
The ``upload_port`` is given by the name set in the OTA declaration.
``--auth`` is the password set in ``ArduinoOTAPassword`` 

.. code-block:: 
   :linenos:

   [env:OTA]
   platform = platformio/espressif32
   board = esp32-s3-devkitm-1
   framework = arduino
   upload_protocol = espota
   upload_port = EvoX1-OTA.local
   upload_flags = --host_port=55910, --auth=admin


