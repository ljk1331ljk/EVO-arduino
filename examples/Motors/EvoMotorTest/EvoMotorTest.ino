#include <Evo.h>
#include <EvoMotor.h>
EVO evo;
EvoMotor left(M1, true);
EvoMotor right(M2);

void setup()
{
  evo.begin();
  evo.clearDisplay();
  evo.writeToDisplay("Motor test", 0, 0, true, true);
  left.begin();
  right.begin();
  left.run(2000);
  right.run(2000);
  delay(1000);
  left.coast();
  right.coast();
  evo.playTone(300, 200);
}

void loop()
{
  evo.clearDisplay();
  evo.writeToDisplay(left.getAngle(), 0, 0);
  evo.writeToDisplay(right.getAngle(), 0, 8);
  evo.drawDisplay();

  // put your main code here, to run repeatedly:
}
