#include <Evo.h>

EVOX1 evo;
EvoTOF dist(I2C1);

void setup()
{
  evo.begin();
  dist.begin();

  evo.writeToDisplay("EvoTOF Test", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.writeToDisplay("Press button to begin", 0, 32, false, true);

  evo.waitForBump();
}

int distance;
void loop()
{
  distance = dist.getDistance();
  evo.clearDisplay();

  evo.writeToDisplay("Distance:", 0, 0);
  evo.writeToDisplay(distance, 60, 0);

  evo.drawDisplay();
}