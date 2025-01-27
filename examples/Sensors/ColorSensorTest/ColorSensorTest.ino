#include <EV3ColorSensor.h>

EV3ColorSensor colorSensor(S1);

void setup() {
  Serial.begin(115200);
  //initializes the color sensor
  colorSensor.begin();
  //sets the mode of the color sensor
  colorSensor.setMode(EV3ColorSensorMode::COL_REFLECT);
  // colorSensor.setMode(EV3ColorSensorMode::COL_AMBIENT);
  // colorSensor.setMode(EV3ColorSensorMode::COL_COLOR;
}
int timenow = 0;
void loop() {
  timenow = millis();
  while ((millis() - timenow) < 3000) {
    Serial.print("Reflected: ");
    Serial.println(colorSensor.getReflection());
  }

  timenow = millis();
  while ((millis() - timenow) < 3000) {
    Serial.print("Ambient: ");
    Serial.println(colorSensor.getAmbient());
  }

  timenow = millis();
  while ((millis() - timenow) < 3000) {
    Serial.print("Color: ");
    Serial.print(colorSensor.getColor());
    Serial.print(" , ");
    Serial.println(toColor(colorSensor.getColor()));
  }
}
