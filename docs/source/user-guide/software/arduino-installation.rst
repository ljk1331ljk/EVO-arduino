Arduino IDE [Recommended]
=========================

The Arduino IDE 2 is an improvement of the classic IDE, with increased performance, improved user interface and many new features, such as autocompletion, a built-in debugger and syncing sketches with Arduino Cloud.

.. note:: 

   You will need to use Arduino IDE 2.X to program the EVOX1. If you are using Arduino IDE 1.X, you will not be able to program the EVOX1.

IDE Installation
----------------

.. card:: Steps to Download Arduino IDE

   1. Go to the official Arduino IDE `download page <https://www.arduino.cc/en/software>`_

   2. Download the version for your operating system:

      * Windows: ``.exe`` installer or ``.zip`` (portable version)
      * Mac: ``.dmg`` installer
      * Linux: ``.AppImage`` or ``package`` for your distribution

   3. Install Arduino IDE by following the on-screen instructions

Board Installation
------------------

.. grid:: 2

   .. grid-item::

      1. Open the Boards Manager from the left panel
      2. Search for "esp32"
      3. Install **esp32 by Espressif Systems** board

   .. grid-item::

      .. figure:: /_static/images/library-board-install-ino.png
         :alt: ESP32 Board
         :width: 100%
         :align: center

Library Installation
--------------------

1. Go to to the `Evo Github Releases Page <https://github.com/ljk1331ljk/EVO-arduino/releases>`_

2. Download the Source code ``.zip`` under Assets from the latest release.

3. In ArduinoIDE:

   - Click on Sketch on the top left bar
   - Include Library 
   - Add ``.zip`` Library and 
   - Select the file just downloaded.

   .. figure:: /_static/gifs/install-library-ino.gif
      :alt: Revealing Library Folder in Explorer
      :width: 100%
      :align: center

4. Go to the Libraries tab and search for the libraries listed below. Install them as such.

   * ``Adafruit NeoPixel`` by Adafruit
   * ``Adafruit PWM Servo Driver Library`` by Adafruit
   * ``EspSoftwareSerial`` by Dirk Kaar, Peter Lerup
   * ``ESP32Encoder`` by Kevin Harrington
   * ``Adafruit VL53L0X`` by Adafruit
   * ``Adafruit TCS34725`` by Adafruit
   * ``Adafruit BNO055`` by Adafruit

   .. warning::

      This list may grow over time, so check back here when new updates are released.

Updating EVO Library
--------------------

To update the EVO library when there is a new relsease available repeat the steps in :ref:`Library Installation` and the library will be overwritten.