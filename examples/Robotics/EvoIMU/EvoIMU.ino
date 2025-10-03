#include <EvoAdv.h>

EVOX1 evo;

EvoMotor motorLeft(M3, ITERMKS);
EvoMotor motorRight(M4, ITERMKS, true);
EvoMotorPair robot(&motorLeft, &motorRight);
EvoBNO055 bno(I2C8);
EvoIMU IMU(&bno, &motorLeft, &motorRight);

float x, y, z, heading;

void setup() {
  Serial.begin(115200); // Initialize Serial communication
  evo.begin();
  IMU.begin();  // Initialize the trace object

  evo.writeToDisplay("BNO055 IMU Adv Test", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.writeToDisplay("Press button to begin", 0, 32, false, true);

  evo.waitForBump();

  bno.resetHeading();
  heading = bno.getRelativeHeading();
  evo.clearDisplay();
  evo.writeToDisplay(heading, 0, 0);
  evo.drawDisplay();

  evo.waitForBump();

  IMU.move(800, 800, 1000);
  delay(500);
  IMU.move(1000, 0, 90);
  delay(500);
  IMU.move(-1000, 0, 90);
  delay(500);
  IMU.move(0, -1000, 90);
  delay(500);
  IMU.move(0, 1000, 90);
  delay(500);
  IMU.move(1000, -1000, 90);

  delay(500);
  robot.coast();
}


void loop() {
  bno.getEuler(&x, &y, &z);
  heading = bno.getRelativeHeading();
  evo.clearDisplay();

  evo.writeToDisplay("X:", 0, 0);
  evo.writeToDisplay(x, 30, 0);

  evo.writeToDisplay("Y:", 0, 16);
  evo.writeToDisplay(y, 30, 16);

  evo.writeToDisplay("X:", 0, 32);
  evo.writeToDisplay(y, 30, 32);

  evo.writeToDisplay("H:", 0, 48);
  evo.writeToDisplay(heading, 30, 48);

  evo.drawDisplay();

  if (evo.getButton() == PRESSED)
  {
    bno.resetHeading();
  }
}
