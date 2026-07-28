#include <Evo.h>

EvoX1E evo;

EvoMotor leftMotor(M1, ITERMK330, true);
EvoMotor rightMotor(M2, ITERMK330);

const int MAX_SPEED = 1500;
const unsigned long RAMP_TIME_MS = 2000;
const unsigned long CRUISE_TIME_MS = 1000;
const unsigned long UPDATE_INTERVAL_MS = 10;

// Quintic smoothstep: position, velocity, and acceleration change smoothly.
float sCurve(float progress)
{
  progress = constrain(progress, 0.0f, 1.0f);
  return progress * progress * progress *
         (progress * (progress * 6.0f - 15.0f) + 10.0f);
}

void setDriveSpeed(int speed)
{
  leftMotor.run(speed);
  rightMotor.run(speed);
}

void rampSpeed(int startSpeed, int endSpeed, unsigned long durationMs)
{
  unsigned long startTime = millis();
  unsigned long elapsed = 0;

  while (elapsed < durationMs)
  {
    float progress = (float)elapsed / durationMs;
    float blend = sCurve(progress);
    int speed = startSpeed + (int)((endSpeed - startSpeed) * blend);

    setDriveSpeed(speed);
    delay(UPDATE_INTERVAL_MS);
    elapsed = millis() - startTime;
  }

  setDriveSpeed(endSpeed);
}

void setup()
{
  evo.begin();
  leftMotor.begin();
  rightMotor.begin();

  evo.writeToDisplay("S-curve ready", 0, 0, true, true);
  evo.waitForBump();

  rampSpeed(0, MAX_SPEED, RAMP_TIME_MS);
  delay(CRUISE_TIME_MS);
  rampSpeed(MAX_SPEED, 0, RAMP_TIME_MS);

  leftMotor.brake();
  rightMotor.brake();
  evo.writeToDisplay("Complete", 0, 0, true, true);
}

void loop()
{
}
