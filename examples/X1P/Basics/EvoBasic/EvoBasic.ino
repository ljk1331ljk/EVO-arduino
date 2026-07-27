#include <Evo.h>

EvoX1P evo;

void setup()
{
  Serial.begin(115200);
  evo.begin();

  Serial.print("EVO library: ");
  Serial.println(EVO_LIBRARY_VERSION);
  Serial.print("Controller: ");
  Serial.println(evo.getControllerName());
  Serial.print("Motor ports: ");
  Serial.println(evo.getMotorCount());
  Serial.print("Servo ports: ");
  Serial.println(evo.getServoCount());

  evo.playTone(880, 100);
}

void loop()
{
}
