#include <EVO.h>

EVOX1 evo;
EV3ColorSensor colorSensor(S1);

void setup()
{
  Serial.begin(115200);
  // initializes the color sensor
  evo.begin();
  colorSensor.begin();
  delay(2000);

  // sets the mode of the color sensor
  colorSensor.setMode(EV3ColorSensorMode::COL_REFLECT);
  // colorSensor.setMode(EV3ColorSensorMode::COL_AMBIENT);
  // colorSensor.setMode(EV3ColorSensorMode::COL_COLOR;

  evo.clearDisplay();
  evo.writeToDisplay("Color sensor test", 0, 0, true, true);

  evo.waitForBump();
}
unsigned long timenow = 0;
int value;
void loop()
{
  timenow = millis();
  while ((millis() - timenow) < 3000)
  {
    evo.writeToDisplay("Reflection:", 0, 0, true);
    evo.writeToDisplay(colorSensor.getReflection(), 80, 0, false, true);
  }

  timenow = millis();
  while ((millis() - timenow) < 3000)
  {
    evo.writeToDisplay("Ambient:", 0, 0, true);
    evo.writeToDisplay(colorSensor.getAmbient(), 80, 0, false, true);
  }

  timenow = millis();
  while ((millis() - timenow) < 3000)
  {
    evo.writeToDisplay("Color:", 0, 0, true);
    evo.writeToDisplay(toColor(colorSensor.getColor()), 80, 0, false, true);
  }
}