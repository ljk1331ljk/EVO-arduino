Connecting to Evo
=================

Wired
-----

Connect the Evo via the Type-C port to your computer. The **COM Port** will be shown in the IDE.

Selecting Board & Port
^^^^^^^^^^^^^^^^^^^^^^

**Arduino**

1. Connect the EVOX1 to the computer and turn it on. A new port will appear in the drop down on the top left corner

.. figure:: /_static/images/board-port-selection-1-ino.png
   :alt: Board & Port Dropdown
   :width: 50%
   :align: center

2. Click on Select other board and port...

3. Search for **ESP32S3 Dev Module** and make sure that the correct **COM Port** is selected

.. figure:: /_static/images/board-port-selection-2-ino.png
   :alt: Board & Port Selection
   :width: 100%
   :align: center

**PlatformIO**

By default, PlatformIO can recognise ports and will automatic set COM port for you (Auto). If you wish to specify the port, you can select them from the PlatformIO Toolbar.

- PlatformIO: Home
- PlatformIO: Build
- PlatformIO: Upload
- PlatformIO: Clean
- PlatformIO: Serial Monitor
- **Set Port [Select This]**

.. figure:: /_static/images/toolbar-setport-pio.png
   :alt: Toolbar Selection
   :width: 100%
   :align: center

Enabling USB Serial Port
^^^^^^^^^^^^^^^^^^^^^^^^

The EVOX1 uses the USB peripheral pins for program upload and serial communication. 

**Arduino**

To enable the serial port, click on tools :octicon:`arrow-right` USB CDC on Boot :octicon:`arrow-right` Enabled

.. figure:: /_static/gifs/enable-usb-cdc-ino.gif
   :alt: USB CDC Enabled
   :width: 100%
   :align: center

**PlatformIO**

To enable the serial port, include this line at the end of the code in ``platformio.ini``

.. code-block:: ini

   build_flags = -DARDUINO_USB_CDC_ON_BOOT=1

   monitor_speed = 115200
   upload_port = COM4 
   monitor_port = COM4

.. Bluetooth
.. ---------

.. Bluetooth Classic VS BLE
.. ^^^^^^^^^^^^^^^^^^^^^^^^

.. The ESP32S3 Dev Modules has a built-in BLE capabilities. A Bluetooth Classic module, HC-05 is also added onto the Evo to give the device bluetooth classic capabilities.

.. Bluetooth Classic is good for sending a lot of data continuously, like in wireless speakers or when connecting to a robot for real-time control. The bluetooth module supports the Serial Port Profile (SPP), which lets devices send serial (UART) data wirelessly—very useful in robotics and embedded systems.

.. Bluetooth Low Energy (BLE), on the other hand, is designed to save power. It’s better for devices that only need to send small amounts of data once in a while, like fitness bands or sensors. BLE doesn’t support serial communication directly, so it needs extra setup to send data like UART.

.. Key Differences:

.. - **Bluetooth Classic**: Higher speed, more power usage, supports wireless serial (SPP).
.. - **BLE**: Lower power, slower speed, no native serial support.

.. When to Use:

.. - Use **Bluetooth Classic** for things like live control or audio.
.. - Use **BLE** for low-power devices that don’t need to send data all the time.

.. Naming the Evo
.. ^^^^^^^^^^^^^^

.. Ensure the Bluetooth module is working by observing how the LED behaves. See the behaviours in :ref:`On-Board Peripherals`.

.. Open the ``EvoHC05.ino`` program 

.. **Arduino:** 

.. - Click on Files :octicon:`arrow-right` Examples :octicon:`arrow-right` EVO :octicon:`arrow-right` Evo Basics :octicon:`arrow-right` EvoHC05

.. .. figure:: /_static/images/open-bluetooth-program-ino.png
..    :alt: Bluetooth Program
..    :width: 100%
..    :align: center

.. **PlatformIO:** 

.. - Navigate to ``lib\Evo\examples\Basics\EvoHC05``. 

.. .. note:: 
   
..    Ensure to copy the code into the ``src/main.ino`` file, as PlatformIO only compiles the code in the ``src`` folder.

.. .. figure:: /_static/gifs/opening-hc05-pio.gif
..    :alt: Opening EvoHC05
..    :width: 100%
..    :align: center

.. In the program, you are able to change the name of the Evo by editing the ``DEVICE_NAME``. Doing so will allow you to identify the Evo from your computer.

.. Debugging the Bluetooth Connection
.. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. When you upload the ``EvoHC05.ino`` program, the Evo will start to communicate with the Bluetooth module. A series of text will appear on the OLED screen which allows you to monitor the connection status.

.. .. list-table:: List of Display Text Shown on Evo
..    :header-rows: 1
..    :widths: 30 70

..    * - Display Text
..      - What it means
..    * - ``AT Mode set``
..      - Switched to AT command mode
..    * - ``checking response``
..      - Waiting for AT response from the module
..    * - ``Response available``
..      - Module is responding
..    * - ``Factory settings set``
..      - Successfully reset to factory defaults
..    * - ``Name set/not set``
..      - Device name was (or wasn't) updated
..    * - ``Baudrate set/not set``
..      - Baud rate update success or failure
..    * - ``BL Mode set``
..      - Switched to normal Bluetooth (communication) mode
..    * - ``Bluetooth is setup``
..      - Setup process is complete

.. .. note:: 

..    If you did not managed to reach the end, this means the BT module is not working or the connection is not successful

.. Open Bluetooth & other Devices Setting on your computer 

.. - :kbd:`⌘` + :kbd:`A` (Windows)

.. Turn on Bluetooth, and connect the Evo of the selected name. Ensure the Blue LED is blinking once every 2 seconds (Bluetooth Connected).