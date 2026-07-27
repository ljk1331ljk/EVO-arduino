#include <Evo.h>

EvoX1P evo;

void setup()
{
  Serial.begin(115200);
  delay(3000); // Wait for serial monitor to open
  evo.begin();
  evo.clearDisplay();
  evo.writeLineToDisplay(("EVO library " + String(EVO_LIBRARY_VERSION)).c_str(), 0);
  evo.writeLineToDisplay(("Controller: " + String(evo.getControllerName())).c_str(), 1);
  evo.writeLineToDisplay(("Motor ports: " + String(evo.getMotorCount())).c_str(), 2);
  evo.writeLineToDisplay(("Servo ports: " + String(evo.getServoCount())).c_str(), 3);
  evo.writeLineToDisplay(("Battery: " + String(evo.getBattery())).c_str(), 4);
  evo.drawDisplay();

  Serial.print("EVO library: ");
  Serial.println(EVO_LIBRARY_VERSION);
  Serial.print("Controller: ");
  Serial.println(evo.getControllerName());
  Serial.print("Motor ports: ");
  Serial.println(evo.getMotorCount());
  Serial.print("Servo ports: ");
  Serial.println(evo.getServoCount());
  Serial.print("Battery: ");
  Serial.println(evo.getBattery());

  evo.playTone(880, 100);
}

void loop()
{
}
