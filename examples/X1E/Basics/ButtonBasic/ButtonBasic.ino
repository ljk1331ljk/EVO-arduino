#include <Evo.h>

EvoX1E evo;

void setup()
{
  evo.begin();

  evo.clearDisplay();
  evo.writeLineToDisplay("X1E Button", 0);
  evo.writeLineToDisplay("Press button 1", 2, false, true);

  evo.waitForPress(1, 200);
  evo.writeLineToDisplay("Pressed", 3, false, true);
  evo.playTone(NOTE_G4, 150);

  evo.waitForRelease(1, 200);
  evo.writeLineToDisplay("Released", 4, false, true);
  evo.playTone(NOTE_C5, 150);

  evo.writeLineToDisplay("Bump button 1", 6, false, true);
  evo.waitForBump(1, 200);
}

void loop()
{
  evo.clearDisplay();
  evo.writeLineToDisplay("X1E Button", 0);
  evo.writeToDisplay("Button 1:", 0, 16);
  evo.writeToDisplay(evo.getButton(1), 62, 16, false, true);
  delay(50);
}
