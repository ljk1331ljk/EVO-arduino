#include <Evo.h>

EVOX1 evo;

EvoMotor motorLeft(M3, ITERMKS);
EvoMotor motorRight(M4, ITERMKS, true);
EvoMotorPair robot(&motorLeft, &motorRight);
EvoTCS34725 sensorLeft(I2C7);
EvoTCS34725 sensorRight(I2C8);
EvoTrace trace(&sensorLeft, &sensorRight, &motorLeft, &motorRight);

uint16_t rr, rg, rb, rc, lr, lg, lb, lc;

void setup() {
  Serial.begin(115200); // Initialize Serial communication
  evo.begin();
  trace.begin();  // Initialize the trace object
  sensorLeft.setGain(TCS34725_GAIN_16X);
  sensorRight.setGain(TCS34725_GAIN_16X);

  evo.waitForBump(200); 

  trace.PDTrackDegrees(500, 0.1, 3, 2000);
  trace.PDTrackJunction(500, 0.1, 3, 300, 1);
  delay(500);
  robot.coast();
}


void loop() {
  sensorLeft.getRawRGBC(&lr, &lg, &lb, &lc);
  sensorRight.getRawRGBC(&rr, &rg, &rb, &rc);
  evo.writeLineToDisplay(int(rc), 0, true);
  evo.writeLineToDisplay(int(lc), 1, false, true);
}
