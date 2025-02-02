#include <Evo.h>
#include <EvoMotor.h>
#include <EvoMotorPair.h>

EVOX1 evo;
EvoMotor left(M1, true);
EvoMotor right(M4);
EvoMotorPair robot(&left, &right);

void setup() {
  Serial.begin(115200);
  evo.begin();
  left.begin();
  right.begin();
  evo.writeToDisplay("Program begin", 0, 0, true);
  delay(2000);

  robot.setAcceleration(8, 2000);
  robot.setDeceleration(8, 2000);
  robot.setMinimumSpeed(800);
  robot.setPD(10, 30);

  robot.moveDegrees(2000, 2000, 1000);
  delay(500);
  robot.moveDegrees(-3000, 3000, 500);
  delay(500);
  robot.moveDegrees(2000, 2000, 1000);
  delay(500);
  robot.moveDegrees(-2000, -2000, 1000);
  delay(500);
  robot.moveDegrees(3000, -3000, 500);
  delay(500);
  robot.moveDegrees(-2000, -2000, 1000);
  delay(500); 
  robot.coast();

}

void loop() {

  evo.writeToDisplay("M1:", 0, 0, true);
  evo.writeToDisplay(left.getAngle(), 40, 0);
  evo.writeToDisplay("M2:", 0, 8);
  evo.writeToDisplay(right.getAngle(), 40, 8, false, true);

}
