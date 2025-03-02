#include <Evo.h>

EVOX1 evo;

void setup()
{
  evo.begin(); // initialises the Evo-X1 peripherals

  evo.clearDisplay(); // clears the display buffer
  evo.drawDisplay();  // draws the empty screen

  evo.clearDisplay();
  evo.writeLineToDisplay("Display Basic", 0); // writes the program name to the display
  evo.drawDisplay();

  evo.waitForBump(200);

  /* Drawing something on the screen consists of 2 steps:
   * 1. Filling up a buffer.
   * 2. Drawing on the display itself.
   */
  evo.clearDisplay();               // this line clears the display buffer
  evo.writeToDisplay("Text", 0, 0); // this line fills the buffer with text at (0,0)
  evo.writeToDisplay(12345, 0, 16); // this line fills the buffer with integers at (0,16)
  evo.writeToDisplay(0.123, 0, 24); // this line fills the buffer with float at (0,24)
  evo.drawDisplay();                // this line draws the filled buffer

  evo.waitForBump(200); // wait for button to be pressed and released

  evo.writeToDisplay("Display Basic", 0, 0, true, true); // this line clears the buffer (clear = true), fills the buffer with "Display Basic" and draws on the display (draw = true).

  evo.waitForBump(200); // wait for button to be pressed and released

  evo.writeLineToDisplay("this writes a line", 2, false, true); // writes a line to the display
}

void loop()
{
  delay(1000);
}
