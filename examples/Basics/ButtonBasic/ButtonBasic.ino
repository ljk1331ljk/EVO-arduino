#include <Evo.h>

EVOX1 evo;

void setup()
{
  evo.begin(); // initialises the Evo-X1 peripherals

  evo.clearDisplay(); // clears the display buffer
  evo.drawDisplay();  // draws the empty screen

  evo.clearDisplay();
  evo.writeLineToDisplay("Button Basic", 0); // writes the program name to the display
  evo.drawDisplay();

  evo.writeLineToDisplay("Waiting for press", 2, false, true); // writes and draw a single line on the display
  evo.waitForPress(200);                                       // wait for button press
  evo.playTone(NOTE_G4, 300);                                  // plays the buzzer for 300ms
  evo.writeLineToDisplay("Button pressed", 3, false, true);    // writes and draw a single line on the display

  evo.writeLineToDisplay("Waiting for release", 4, false, true); // writes and draw a single line on the display
  evo.waitForRelease(200);                                       // wait for button release
  evo.playTone(NOTE_G4, 300);                                    // plays the buzzer for 300ms
  evo.writeLineToDisplay("Button released", 5, false, true);     // writes and draw a single line on the display

  evo.writeLineToDisplay("Waiting for bump", 6, false, true); // writes and draw a single line on the display
  evo.waitForBump(200);                                       // waits for the button to be pressed and released
  evo.playTone(NOTE_G4, 300);                                 // plays the buzzer for 300ms
  evo.writeLineToDisplay("Button released", 7, false, true);  // writes and draw a single line on the display

  delay(3000);
}

void loop()
{
  evo.clearDisplay();
  evo.writeLineToDisplay("Button Basic", 0);   // writes the program name to the display
  evo.writeToDisplay("Button State:", 0, 16);  // writes a single line on the display
  evo.writeToDisplay(evo.getButton(), 80, 16); // writes the state of the button on the display
  evo.drawDisplay();
}
