PlatformIO IDE in VSCode
========================

PlatformIO is a cross-platform, cross-architecture, multiple framework, professional tool for embedded systems engineers and for software developers who write applications for embedded products.

IDE Installation
----------------

Before starting make sure to download and install `Visual Studio Code <https://code.visualstudio.com/download>`_.

.. card:: Steps to Download PlatformIO IDE
   
   1. Open VSCode
   2. Go to the Extensions tab & search "PlatformIO"
   3. Click install
   4. When prompted by PlatformIO, restart VSCode

Setting Up the Project
----------------------

Once you're on PlatformIO's Home page, select ``New Project``. The program will then prompt you to choose a name for your project so be creative.

Type in ``Espressif ESP32-S3`` and select the ``Espressif ESP32-S3-DevkitM-1`` board from the boards dropdown menu.

Leave the Framework option on Arduino. The default project path on Windows is ``Documents/PlatformIO/Projects``, but you’re free to save it wherever you like.

After clicking Finish, you’ll need to wait a bit while the board files are downloaded.

.. figure:: /_static/gifs/opening-project-pio.gif
   :alt: Opening Project in PlatformIO
   :width: 100%
   :align: center

Project Structure
--------------------

After creating a new empty PlatformIO project you're ready for the next step. The PlatformIO project structure consists of the following:

.. list-table::
   :widths: 25 75

   * - ``platformio.ini``
     - Project configuration file
   * - ``src`` directory
     - Where you should place source code (``*.h``, ``*.c``, ``*.cpp``, ``*.S``, ``*.ino``, etc.)
   * - ``lib`` directory
     - For the project-specific private libraries.

.. figure:: /_static/images/project-structure-pio.png
   :alt: Revealing Library Folder in Explorer
   :width: 50%
   :align: center

.. note:: 
   
   We will be placing the Evo Library in the ``lib`` folder.

Library Installation
--------------------

1. Go to to the `Evo Github Releases Page <https://github.com/ljk1331ljk/EVO-arduino/releases>`_
2. Download the Source code ``.zip`` under Assets from the latest release.
3. In VSCode Explorer:

   - Right-Click on ``lib`` folder, select "Reveal in File Explorer"

   .. figure:: /_static/gifs/install-library-1-pio.gif
      :alt: Revealing Library Folder in Explorer
      :width: 100%
      :align: center

   - Extract the contents in the ``.zip`` folder into the ``lib`` folder
   - Rename the extracted folder to "Evo"

   .. figure:: /_static/gifs/install-library-2-pio.gif
      :alt: Placing Evo Library in Library Folder
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

5. Go to ``platform.ini`` to ensure the library dependencies ``lip_dep`` are listed correctly. 