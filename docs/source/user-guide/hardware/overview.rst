Overview
========

The EVOX1 is a 3.3V logic microcontroller. Sensors will need to be 3.3V compaitable for correct operation. Although the device is a 3.3V logic microcontroller, it has a 5V rail on the servo ports to provide sufficient power to the servos connected.

Hardware Features
-----------------

The EVOX1 boasts the following features:

.. card:: Ports

   * 4 x EV3 Motor Ports 
   * 4 x Motor Ports with Encoder *(shared pins with EV3 Motor Ports)*
   * 8 x Servo Ports
   * 8 x I2C Multiplexed Ports
   * 4 x EV3 Sensor Ports
   * 8 x GPIO Ports *(shared pins with EV3 Sensor Ports)*
   * 2 x UART/ SPI hybrid port
   * 2 x I2C port

.. card:: Peripherals

   * 4kHz Buzzer
   * 128 x 64 - 1.54 inch OLED Display
   * Programmable Button
   * RGB LED Indicator *(shared pins with Programmable Button)*

.. card:: Wireless Functionalities

   * Bluetooth Classic via inbuilt HC-05
   * Bluetooth Low Energy 5.0
   * Integrated Wi-Fi 4 *(802.11b/g/n, 2.4GHz)*

On-Board Peripherals
--------------------

.. figure:: /_static/images/EVOX1pherperials.png
   :alt: EVOX1 Pherperials
   :width: 100%
   :align: center

.. list-table:: Peripherals
   :widths: 25 75
   :header-rows: 1
   :align: center

   * - Peripheral
     - Description
   * - Power Button
     - | ``On momentary press`` turns the EVOX1 **on**
       | ``On long press`` turns the EVOX1 **off**
   * - Boot Button
     - | ``On momentary press`` puts the EVOX1 into **normal mode**
       | ``On long press`` puts the EVOX1 into **bootloader mode**
   * - Bluetooth Button
     - | ``On momentary press`` turns the **Bluetooth on**
       | ``On long press`` turns the **Bluetooth off**
   * - Programmable Button
     - | Button that can be programmed
       | Must be used as ``INPUT_PULLUP``
       | Connected to the same ``IO14`` as the RGB LED
   * - USB Power LED :bdg-danger:`RED`
     - Indicates power going into the EVOX1 from the USB-C port
   * - Charging LED :bdg-success:`GREEN`
     - | ``Steady`` Charging
       | ``Blinking`` Unable to charge
       | ``Off`` Battery is full
   * - Power On LED :bdg-success:`GREEN`
     - Indicates that the EVOX1 is on
   * - Bluetooth LED :bdg-info:`BLUE`
     - | ``Blink Cnce in 2s`` Bluetooth in command mode / Connected
       | ``Repeated Blinking`` Waiting for connection / Disconnected
       | ``Off`` Bluetooth is off
   * - USB-C Download & Charging
     - Allows download and charging of power
   * - RGB LED
     - | WS2812 RGB LED
       | Connected to the same ``IO14`` as the programmable button
   * - 4kHz Buzzer
     - Programmable buzzer
   * - 128 x 64 OLED Display
     - Programmable OLED Display

Pinouts
-------

.. figure:: /_static/images/EVOX1pinout.png
   :alt: EVOX1 Pinouts
   :width: 100%
   :align: center

Connecting Hardware
-------------------

.. list-table:: Wire Color Codes
   :widths: 25 75
   :header-rows: 1
   :align: center

   * - Color
     - Pin
   * - Black
     - Ground
   * - Red
     - Power
   * - Yellow
     - Data

.. caution:: 
   The pins on the EVOX1 are color coded. Exercise caution when connecting any hardware to the ports.