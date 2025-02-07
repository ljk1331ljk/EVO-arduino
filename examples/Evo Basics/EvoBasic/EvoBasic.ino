#include <Evo.h>

EVOX1 evo;

void setup()
{
  Serial.begin(115200);

  evo.begin(); // initialises the Evo-X1 peripherals

  evo.clearDisplay(); // clears the display buffer
  evo.drawDisplay();  // draws the empty screen

  evo.waitForButton(); // waits for the button to be pressed

  evo.writeToDisplay("test", 0, 0);     // writes character array to the display
  evo.writeToDisplay(123456789, 40, 0); // writes integers to the display
  evo.writeToDisplay(123.456789, 0, 8); // writes double to the display
  evo.drawDisplay();

  // gets battery Level and write to display
  float batteryVoltage = evo.getBattery();
  Serial.print("Battery Voltage: ");
  Serial.println(evo.getBattery());
  evo.writeToDisplay("Battery :", 0, 24);
  evo.writeToDisplay(evo.getBattery(), 60, 24);
  evo.drawDisplay(); // draws the display

  // plays the buzzer for 300ms
  evo.playTone(NOTE_G4, 300);
}
void loop()
{
  // cycling through red green and blue colors using the RGB led
  evo.setRGB(20, 0, 0);
  delay(1000);
  evo.setRGB(0, 20, 0);
  delay(1000);
  evo.setRGB(0, 0, 20);
  delay(1000);
}
