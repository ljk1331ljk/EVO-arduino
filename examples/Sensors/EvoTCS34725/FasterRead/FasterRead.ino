#include <Evo.h>

EVOX1 evo;
EvoTCS34725 cs(I2C8);
uint16_t rr, rg, rb, rc;
float r, g, b;
float h, s, v;


void setup() {
  Serial.begin(115200);
  evo.begin();
  cs.begin();
  evo.writeToDisplay("Color Sensor Test", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.waitForButton();
  cs.setGain(TCS34725_GAIN_16X);
}

void loop() {

  cs.getRawRGBC(&rr, &rg, &rb, &rc);
  cs.getRGB(&r, &g, &b);
  cs.getHSV(&h, &s, &v);

  evo.clearDisplay();
  evo.writeToDisplay("raw:", 0, 0);
  evo.writeToDisplay(int(rr), 35, 0);
  evo.writeToDisplay(int(rg), 58, 0);
  evo.writeToDisplay(int(rb), 81, 0);
  evo.writeToDisplay(int(rc), 104, 0);
  evo.writeToDisplay("Filt:", 0, 16); 
  evo.writeToDisplay(int(r), 35, 16);
  evo.writeToDisplay(int(g), 58, 16);
  evo.writeToDisplay(int(b), 81, 16);
  evo.writeToDisplay("HSV:", 0, 32);
  evo.writeToDisplay(int(h), 35, 32);
  evo.writeToDisplay(int(s), 58, 32);
  evo.writeToDisplay(int(v), 81, 32);
  evo.drawDisplay();

  evo.setRGB(r, g, b);
}