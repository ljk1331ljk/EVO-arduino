#include <Evo.h>

EVOX1 evo;

EvoMotor motor(M3, ITERMKS, true);
/* Available motor types
  GENERICWITHENCODER,
  GENERISWITHOUTENCODER,
  EV3LargeMotor,
  EV3MediumMotor,
  GeekServoDCMotor,
  ITERSpeed,
  ITERTorque,
  EVOMotor300,
  EVOMotor100
*/
void setup()
{
  evo.begin();
  motor.begin();

  evo.clearDisplay();
  evo.writeToDisplay("Motor test", 0, 0, true, true);

  evo.waitForButton();

  motor.runAngle(4000, 360);
  delay(1000);
  motor.runTime(4000, 1000);
  delay(1000);
  motor.resetAngle();
  motor.runTarget(2000, -360, true);
  delay(1000);
  motor.runUntilStalled(2000);
  delay(1000);
  motor.coast();
}

void loop()
{
  evo.clearDisplay();
  evo.writeToDisplay(motor.getAngle(), 0, 0);
  evo.writeToDisplay(motor.getCount(), 0, 8);
  evo.drawDisplay();
}
