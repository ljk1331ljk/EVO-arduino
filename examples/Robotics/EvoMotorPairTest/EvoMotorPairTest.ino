#include <Evo.h>

EVOX1 evo;

EvoMotor leftM(M1, ITERMK330, true);
EvoMotor rightM(M2, ITERMK330);
EvoMotor Mech1(M3, ITERMK330);
EvoMotor Mech2(M4, ITERMK195);
EvoBNO055 bno(I2C8);
EvoMotorPair robot(&leftM, &rightM, &bno);

void setup()
{
  Serial.begin(115200);
  evo.begin();
  leftM.begin();
  rightM.begin();
  bno.begin();
  evo.writeToDisplay("Program begin", 0, 0, true, true);

  evo.waitForBump();

  bno.resetHeading();
  robot.setAcceleration(50, 500);
  robot.setDeceleration(50, 500);
  robot.setPD(100, 30);
  robot.moveTime(-1000, -1000, 1000);
  delay(500);
  robot.moveIMU(2000, 2000, 1000);
  delay(500);
  robot.moveDegrees(1500, -1500, 200);
  delay(500);
  robot.moveIMU(0, 1500, 90);
  delay(500);
  robot.moveIMU(1500, 0, 90);
  delay(500);
  robot.moveIMU(-1500, 0, 45);
  delay(500);
  robot.moveIMU(0, -1500, 45);
  delay(500);
  robot.moveIMU(1500, - 1500, 90);
  delay(500);
}

float x, y, z;
float heading;
void loop()
{
  bno.getEuler(&x, &y, &z);
  heading = bno.getRelativeHeading();

  evo.writeToDisplay("Left:", 0, 0, true);
  evo.writeToDisplay(leftM.getAngle(), 40, 0);
  evo.writeToDisplay("Right:", 0, 8);
  evo.writeToDisplay(rightM.getAngle(), 40, 8);

  evo.writeToDisplay("X:", 0, 16);
  evo.writeToDisplay(x, 30, 16);

  evo.writeToDisplay("Y:", 0, 24);
  evo.writeToDisplay(y, 30, 24);

  evo.writeToDisplay("X:", 0, 32);
  evo.writeToDisplay(y, 30, 32);

  evo.writeToDisplay("H:", 0, 40);
  evo.writeToDisplay(heading, 30, 40, false, true);

  evo.drawDisplay();

  if (evo.getButton() == PRESSED)
  {
    bno.resetHeading();
  }
}