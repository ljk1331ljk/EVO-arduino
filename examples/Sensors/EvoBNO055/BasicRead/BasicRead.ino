#include <Evo.h>

EVOX1 evo;
EvoBNO055 bno(I2C8);

void setup()
{
  evo.begin();
  bno.begin();

  evo.writeToDisplay("BNO055 IMU Test", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.writeToDisplay("Press button to begin", 0, 32, false, true);

  evo.waitForBump();
}

float x, y, z;
float heading;
void loop()
{
  bno.getEuler(&x, &y, &z);
  heading = bno.getRelativeHeading();
  evo.clearDisplay();

  evo.writeToDisplay("X:", 0, 0);
  evo.writeToDisplay(x, 30, 0);

  evo.writeToDisplay("Y:", 0, 16);
  evo.writeToDisplay(y, 30, 16);

  evo.writeToDisplay("X:", 0, 32);
  evo.writeToDisplay(y, 30, 32);

  evo.writeToDisplay("H:", 0, 40);
  evo.writeToDisplay(heading, 30, 40);

  evo.drawDisplay();

  if (evo.getButton() == PRESSED)
  {
    bno.resetHeading();
  }
}