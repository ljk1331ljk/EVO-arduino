LED & Buzzer
============

.. doxygenfunction:: EVOX1::playTone
   :project: API

.. warning::
   `playTone` is **blocking** — it will delay program execution.

.. doxygenfunction:: EVOX1::setRGB
   :project: API

.. tip::
   Use colors to indicate system states — e.g., red = error, green = ready.

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