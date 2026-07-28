#include <Evo.h>

EvoX1E evo;

EvoMotor leftMotor(M1, ITERMK330, true);
EvoMotor rightMotor(M2, ITERMK330);
EvoMotorPair robot(&leftMotor, &rightMotor);

const int START_SPEED = 200;
const int MAX_SPEED = 1500;
const int ACCELERATION = 1000;
const int DECELERATION = 1000;
const int TRAVEL_DEGREES = 3600;

void setup()
{
  evo.begin();
  leftMotor.begin();
  rightMotor.begin();

  evo.writeToDisplay("S-curve ready", 0, 0, true, true);
  evo.waitForBump();

  robot.setStartSpeed(START_SPEED);
  robot.setEndSpeed(START_SPEED);
  robot.setAcceleration(ACCELERATION);
  robot.setDeceleration(DECELERATION);
  robot.setAccelerationProfile(AccelerationProfile::SCurve);
  robot.moveDegrees(MAX_SPEED, MAX_SPEED, TRAVEL_DEGREES, BRAKE);

  evo.writeToDisplay("Complete", 0, 0, true, true);
}

void loop()
{
}
