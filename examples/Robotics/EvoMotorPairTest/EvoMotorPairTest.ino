#include <Evo.h>

EVOX1 evo;

EvoMotor leftM(M1, EV3MediumMotor, true);
EvoMotor rightM(M2, EV3MediumMotor);
EvoMotorPair robot(&left, &right);

void setup()
{
  evo.begin();
  leftM.begin();
  rightM.begin();
  evo.writeToDisplay("Program begin", 0, 0, true, true);

  evo.waitForBump();

  robot.setAcceleration(8, 1000);
  robot.setDeceleration(8, 1000);
  robot.setMinimumSpeed(800);
  robot.setPD(400, 30);
  robot.moveDegrees(2500, 2500, 1000);
  delay(500);
  robot.moveTime(2500, 2500, 1000);
}

void loop()
{
  evo.writeToDisplay("Left:", 0, 0, true);
  evo.writeToDisplay(left.getAngle(), 40, 0);
  evo.writeToDisplay("Right:", 0, 8);
  evo.writeToDisplay(right.getAngle(), 40, 8, false, true);
}