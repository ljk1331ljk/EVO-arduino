#include <Evo.h>

#if defined(EVO_BOARD_X1E)
EvoX1E evo;
#elif defined(EVO_BOARD_X1P)
EvoX1P evo;
#endif

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
