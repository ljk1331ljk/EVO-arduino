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


Library Installation
--------------------

1. Open ``platform.ini`` from your project folder.

2. Add ``lib.deps =https://github.com/ljk1331ljk/EVO-arduino.git`` under the ``[env:esp32-s3-devkitm-1]`` section.

   .. code-block:: ini

      [env:esp32-s3-devkitm-1]
      platform = espressif32
      board = esp32-s3-devkitm-1
      framework = arduino
      lib.deps =https://github.com/ljk1331ljk/EVO-arduino.git
      

3. Save the file and PlatformIO will download the library.