Board
=====

.. doxygenclass:: EVOX1
   :project: API

.. rubric:: Initialisation & Setup

.. doxygenfunction:: EVOX1::begin
   :project: API

I2C Control Functions
---------------------

.. doxygenfunction:: EVOX1::selectI2CChannel
   :project: API

.. doxygenfunction:: EVOX1::scanI2CChannel
   :project: API

Example
^^^^^^^

.. code-block:: cpp
   :linenos:

   #include <Evo.h>

   EVOX1 evo;

   void setup()
   {
      evo.begin();
      Serial.begin(115200);
      while (!Serial) // Waits for serial to be connected
         ;
      Serial.println("I2C Scanner");
      delay(1000);
      Serial.println("0x70 is the address of the multiplexor. It will show up on every I2C port.");

      int maxAddresses = 5;
      int numAddress = 0;
      uint8_t i2CAddress[maxAddresses];
      for (int i = 0; i < 8; i++)
      {
         numAddress = evo.scanI2CChannel((I2CChannel)i, i2CAddress, maxAddresses);
         if (numAddress != 0)
         {
         Serial.printf("%d addresse(s) found on I2C%d:", numAddress, i + 1);
         for (int j = 0; j < numAddress; j++)
         {
            Serial.printf(" 0x%x", i2CAddress[j]);
         }
         Serial.println();
         }
      }
   }

.. dropdown:: Output
   
   ::

      0x70 is the address of the multiplexor. It will show up on every I2C port.
      2 addresse(s) found on I2C1: 0x29 0x70
      2 addresse(s) found on I2C2: 0x29 0x70
      1 addresse(s) found on I2C3: 0x70
      1 addresse(s) found on I2C4: 0x70
      1 addresse(s) found on I2C5: 0x70
      1 addresse(s) found on I2C6: 0x70
      1 addresse(s) found on I2C7: 0x70
      3 addresse(s) found on I2C8: 0x29 0x3c 0x70

   .. note::
      
      The output will vary depending on the connected devices and their addresses.

Battery Control Functions
-------------------------

.. doxygenfunction:: EVOX1::getTopBattery
   :project: API

.. doxygenfunction:: EVOX1::getBottomBattery
   :project: API

.. doxygenfunction:: EVOX1::getBattery
   :project: API

.. note::
   Battery values are returned in **volts**. Make sure to scale appropriately if using raw ADCs elsewhere.

Example
^^^^^^^

.. code-block:: cpp
   :linenos:

   #include <Evo.h>

   EVOX1 evo;

   void setup() {
      Serial.begin(115200);
      evo.begin();
      Serial.println("EVOX1 evo Initialised");
   }

   void loop() {
      Serial.print("Top Battery: ");
      Serial.print(evo.getTopBattery());
      Serial.print(" V, Bottom Battery: ");
      Serial.print(evo.getBottomBattery());
      Serial.println(" V");
      delay(1000);
   }

Button Control Functions
------------------------

.. doxygenfunction:: EVOX1::waitForButton
   :project: API

.. doxygenfunction:: EVOX1::waitForPress
   :project: API

.. doxygenfunction:: EVOX1::waitForRelease
   :project: API

.. doxygenfunction:: EVOX1::waitForBump
   :project: API

.. doxygenfunction:: EVOX1::getButton
   :project: API

.. important::
   Avoid using `waitForButton()` in loops — prefer `waitForBump()` for debounce reliability.

Display Control Functions
-------------------------

.. doxygenfunction:: EVOX1::flipDisplayOrientation
   :project: API

.. doxygenfunction:: EVOX1::clearDisplay
   :project: API

.. rubric:: Writing to Display

.. doxygenfunction:: EVOX1::writeToDisplay(int, int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeToDisplay(double, int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeToDisplay(const char *, int, int, bool, bool)
   :project: API

.. note::
   These overloaded functions write data to the display at specific coordinates (x, y).
   You can write integers, floating-point values, or C-style strings.
   The optional `clear` parameter clears the display before writing,
   and the optional `draw` parameter immediately renders the display buffer.

.. rubric:: Writing Line to Display

.. doxygenfunction:: EVOX1::writeLineToDisplay(int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeLineToDisplay(double, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeLineToDisplay(const char *, int, bool, bool)
   :project: API

.. note::
   These methods write a value to a specified line on the display.
   Overloads accept integers, floating point numbers, or C-style strings.

.. tip::
   For centered or multiline display, calculate position before calling these methods.

.. doxygenfunction:: EVOX1::drawDisplay
   :project: API

.. doxygenfunction:: EVOX1::setFontSize
   :project: API

Example
^^^^^^^

Here is an example of how to use the EVOX1 display functions

.. code-block:: cpp
   :linenos:

   #include <Evo.h>

   EVOX1 evo;

   void setup() {
      evo.begin();        // Initialize EVOX1

      evo.clearDisplay(); // Clear the display
      evo.writeToDisplay("Hello, EVOX1!", 0, 0, true, true); // Write to display
      evo.drawDisplay();  // Render the display buffer
   }

LED & Buzzer Control Functions
------------------------------

.. doxygenfunction:: EVOX1::setRGB
   :project: API

.. tip::
   Use colors to indicate system states — e.g., red = error, green = ready.

.. doxygenfunction:: EVOX1::playTone
   :project: API

.. warning::
   `playTone` is **blocking** — it will delay program execution.

Example
^^^^^^^

.. code-block:: cpp
   :linenos:

   #include <Evo.h>

   EVOX1 evo;

   void setup() {
   evo.begin(); // initialises the Evo-X1 peripherals

   evo.clearDisplay(); // clears the display buffer
   evo.writeLineToDisplay("Press Button", 0, false, true); // writes the program name to the display

   evo.waitForBump(100);       // waits for the button to be pressed
   evo.playTone(NOTE_G4, 300); // plays the buzzer for 300ms
   }

   void loop() {
   // cycling through red green and blue colors using the RGB led
   evo.setRGB(20, 0, 0);
   delay(1000);
   evo.setRGB(0, 20, 0);
   delay(1000);
   evo.setRGB(0, 0, 20);
   delay(1000);
   }