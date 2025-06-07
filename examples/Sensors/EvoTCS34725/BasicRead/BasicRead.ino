#include <Evo.h>

EVOX1 evo;
EvoTCS34725 cs(I2C1);

void setup()
{
  evo.begin();
  cs.begin();
  evo.writeToDisplay("Basic Color Read", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.waitForBump();
}

void loop()
{
  evo.clearDisplay();

  evo.writeToDisplay("Filtered", 80, 0);
  evo.writeToDisplay("Raw", 40, 0);

  evo.writeToDisplay("Red:", 0, 8);
  evo.writeToDisplay(cs.getRed(), 80, 8);
  evo.writeToDisplay(cs.getRawRed(), 40, 8);

  evo.writeToDisplay("Green:", 0, 24);
  evo.writeToDisplay(cs.getGreen(), 80, 24);
  evo.writeToDisplay(cs.getRawGreen(), 40, 24);

  evo.writeToDisplay("Blue:", 0, 40);
  evo.writeToDisplay(cs.getBlue(), 80, 40);
  evo.writeToDisplay(cs.getRawBlue(), 40, 40);

  evo.writeToDisplay("Clear:", 0, 56);
  evo.writeToDisplay(cs.getRawClear(), 40, 56);
  evo.drawDisplay();
}
