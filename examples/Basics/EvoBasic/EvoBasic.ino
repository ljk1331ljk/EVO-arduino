#include <Evo.h>

EVOX1 evo;

void setup()
{
  evo.begin(); // initialises the Evo-X1 peripherals

  evo.clearDisplay(); // clears the display buffer
  evo.drawDisplay();  // draws the empty screen

  evo.clearDisplay();
  evo.writeLineToDisplay("EvoBasic", 0);       // writes the program name to the display
  evo.writeToDisplay("Evo Lib. Ver.", 0, 16);  // writes character array to the display
  evo.writeToDisplay(LIBRARY_VERSION, 80, 16); // writes integers to the display
  evo.writeToDisplay("Battery :", 0, 32);
  evo.writeToDisplay(evo.getBattery(), 60, 32); // gets the battery level and displays on the screen
  evo.drawDisplay();                            // draws the display

  evo.waitForBump(100);       // waits for the button to be pressed
  evo.playTone(NOTE_G4, 300); // plays the buzzer for 300ms
}
void loop()
{
  // cycling through red green and blue colors using the RGB led
  evo.setRGB(20, 0, 0);
  delay(1000);
  evo.setRGB(0, 20, 0);
  delay(1000);
  evo.setRGB(0, 0, 20);
  delay(1000);
}
