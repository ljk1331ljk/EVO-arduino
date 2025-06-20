Programming with Arduino IDE
============================

Before you can start, you need to set it up and install the necessary softwares. This guide will walk you through the initial steps to get your Evo ready for programming.  

IDE Installation
----------------

.. card:: Arduino IDE 2.X 
   :link: https://www.arduino.cc/en/software

   You will need to use Arduino IDE 2.X to program the EVOX1. If you are using Arduino IDE 1.X, you will not be able to program the EVOX1.

.. card:: Steps to Download

   1. Go to the official Arduino IDE `download page <https://www.arduino.cc/en/software>`_

   2. Download the version for your operating system:

      * Windows: ``.exe`` installer or ``.zip`` (portable version)
      * Mac: ``.dmg`` installer
      * Linux: ``.AppImage`` or ``package`` for your distribution

   3. Install Arduino IDE by following the on-screen instructions

Evo Board Installation
----------------------

.. grid:: 2

   .. grid-item-card::

      1. Click on the Boards Manager on the left panel.
      2. Search for esp32.
      3. Install the board **esp32 by Espressif Systems**
   
   .. grid-item::

      .. figure:: ../_static/images/esp32board.png
         :alt: ESP32 Board
         :width: 600px
         :align: center

Evo Library Installation
------------------------

1. Go to to the `Evo Github Releases Page <https://github.com/ljk1331ljk/EVO-arduino/releases>`_

2. Download the Source code ``.zip`` under Assets from the latest release.

3. In ArduinoIDE

   - Click on Sketch on the top left bar
   - Include Library 
   - Add ``.zip`` Library and 
   - Select the file just downloaded.

   .. figure:: ../_static/images/addziplibrary.png
      :alt: Add to ZIP Libary
      :width: 600px
      :align: center


4. There are other dependencies that needs to be installed manually. Search for the following libraries under the library manager and install them. This list of libraries can increase over time. Do check this section from time to time when there are new releases available.

.. admonition:: Search these Libraries

   * Adafruit NeoPixel by Adafruit
   * Adafruit PWM Servo Driver Library by Adafruit
   * EspSoftwareSerial by Dirk Kaar, Peter Lerup
   * ESP32Encoder by Kevin Harrington
   * Adafruit VL53L0X by Adafruit
   * Adafruit TCS34725 by Adafruit

Updating EVO Library
--------------------

To update the EVO library when there is a new relsease available repeat the steps in :ref:`EVO Library Installation` and the library will be overwritten.

Using V2.0 Hardware
-------------------

If you are using V2.0 hardware. you need to perform the following steps to edit your library. 

1. Go to you Arduino library folder. If it has not been changed, it will be at ``Documents/Arduino/libraries``.
2. Go to ``EVO/src/helper`` and open the ``X1pins.h`` file.
3. Comment out line 4 and save the changes.

.. code-block:: Arduino
   :linenos:
   :emphasize-lines: 4

   #ifndef X1PINS_H
   #define X1PINS_H

   // #define V3_0

   #ifdef V3_0

   // rest of the code

4. To verify which version of pin configuration you are using, you can display ``PIN_VERSION`` on the serial monitor or on the display.
5. To revert to using V3.0 pin configuration, uncomment line 4 and save the changes.
