Connecting to Evo
=================

USB-C
-----

Connect the Evo via the Type-C port to your computer. The **COM Port** will be shown in the IDE.

Arduino
^^^^^^^

1. Connect the EVOX1 to the computer and turn it on. A new port will appear in the drop down on the top left corner

.. figure:: /_static/images/ESP32-board-port-selection-1.png
   :alt: Board & Port Dropdown
   :width: 50%
   :align: center

2. Click on Select other board and port...

3. Search for **ESP32S3 Dev Module** and make sure that the correct **COM Port** is selected

.. figure:: /_static/images/ESP32-board-port-selection-2.png
   :alt: Board & Port Selection
   :width: 100%
   :align: center

PlatformIO
^^^^^^^^^^

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

Bluetooth
---------

Ensure the Bluetooth module is working by observing how the LED behaves. See the behaviours in :ref:`Peripherals`.

1. Open the ``EvoHC05.ino`` program 

   - **Arduino:** Files :octicon:`arrow-right` Examples :octicon:`arrow-right` EVO :octicon:`arrow-right` Evo Basics :octicon:`arrow-right` EvoHC05
   
   .. figure:: /_static/images/open-bluetooth-program.png
      :alt: Bluetooth Program
      :width: 100%
      :align: center
   
   - **PlatformIO:** ``lib\Evo\examples\Basics\EvoHC05``

   .. figure:: /_static/gifs/opening-hc05-pio.gif
      :alt: Opening EvoHC05
      :width: 100%
      :align: center

2. In the program, you are able to change the name of the Evo by editing the ``DEVICE_NAME``

   .. important:: 

      PlatformIO compilies the programs only in the ``src`` folder. If you wish to use example programs, copy & paste them inside the ``src/main.ino``.

3. Upload the program into the Evo and watch the display text carefuly

   .. list-table:: List of Display Text Shown on Evo
      :header-rows: 1
      :widths: 30 70

      * - Display Text
        - What it means
      * - ``AT Mode set``
        - Switched to AT command mode
      * - ``checking response``
        - Waiting for AT response from the module
      * - ``Response available``
        - Module is responding
      * - ``Factory settings set``
        - Successfully reset to factory defaults
      * - ``Name set/not set``
        - Device name was (or wasn't) updated
      * - ``Baudrate set/not set``
        - Baud rate update success or failure
      * - ``BL Mode set``
        - Switched to normal Bluetooth (communication) mode
      * - ``Bluetooth is setup``
        - Setup process is complete

   .. note:: 
   
      If you did not managed to reach the end, this means the BT module is not working or the connection is not successful

4. Open Bluetooth & other Devices Setting on your computer 

   - :kbd:`⌘` + :kbd:`A` (Windows)

5. Turn on Bluetooth, and connect the Evo of the selected name
