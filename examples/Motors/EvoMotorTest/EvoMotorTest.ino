#include <EVO.h>

EVOX1 evo;

EvoMotor motor(M4, GENERICWITHENCODER, true);
/* available motor types
  GENERICWITHENCODER,
  GENERISWITHOUTENCODER,
  EV3LargeMotor,
  EV3MediumMotor,
  GeekServoDCMotor,
  ITERSpeed,
  ITERTorque
*/
void setup()
{
  evo.begin();
  motor.begin();

  evo.clearDisplay();
  evo.writeToDisplay("Motor test", 0, 0, true, true);

  evo.waitForButton();

  motor.runDegrees(4000);
  delay(1000);
  motor.brake();
  evo.waitForButton();
  motor.run(-4000);
  delay(2000);
  motor.coast();
  evo.playTone(300, 200);
}

void loop()
{
  evo.clearDisplay();
  evo.writeToDisplay(motor.getAngle(), 0, 0);
  evo.drawDisplay();
}
