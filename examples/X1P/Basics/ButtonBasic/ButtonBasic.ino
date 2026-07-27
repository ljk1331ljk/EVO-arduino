#include <Evo.h>

EvoX1P evo;

void waitForEachButton()
{
  for (uint8_t button = 1; button <= 3; ++button)
  {
    evo.clearDisplay();
    evo.writeLineToDisplay("X1P Buttons", 0);
    evo.writeToDisplay("Bump button:", 0, 16);
    evo.writeToDisplay(button, 78, 16, false, true);
    evo.waitForBump(button, 200);
    evo.playTone(NOTE_G4 + (button * 100), 150);
  }
}

void setup()
{
  evo.begin();
  waitForEachButton();
}

void loop()
{
  evo.clearDisplay();
  evo.writeLineToDisplay("X1P Buttons", 0);

  for (uint8_t button = 1; button <= 3; ++button)
  {
    evo.writeToDisplay("Button", 0, 8 + (button * 12));
    evo.writeToDisplay(button, 42, 8 + (button * 12));
    evo.writeToDisplay(":", 50, 8 + (button * 12));
    evo.writeToDisplay(evo.getButton(button), 58, 8 + (button * 12));
  }

  evo.drawDisplay();
  delay(50);
}
