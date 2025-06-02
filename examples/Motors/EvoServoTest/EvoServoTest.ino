#include <Evo.h>

EVOX1 evo;
EvoServo ser(SERVO1, GeekServo360Grey);
/* Available servo types
  Default,
  SG90,
  GeekServo360Grey,    // Grey
  GeekServo360Orange,  // Orange
  GeekServoContinuous, // Green
*/

void setup()
{
  evo.begin();
  ser.begin();

  evo.clearDisplay();
  evo.writeToDisplay("Servo test", 0, 0, true, true);

  evo.waitForBump();

  ser.write(0);
  delay(1000);
  ser.write(90);
  delay(1000);
  ser.write(180);
}

void loop()
{
  delay(1000);
}
