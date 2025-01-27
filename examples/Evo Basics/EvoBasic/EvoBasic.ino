#include <EVO.h>

EVO evo;

void setup()
{
  Serial.begin(115200);
  while(!Serial) {}
  Serial.println("Program Started");

  evo.begin(); //initialises the Evo-X1 peripherals

  evo.clearDisplay(); // Clears the display
  evo.drawDisplay();
  delay(1000);
  evo.writeToDisplay("test", 0, 0);// writes character array to the display
  evo.writeToDisplay(123456789, 40, 0); // writes integers to the display
  evo.writeToDisplay(123.456789, 0, 8); // writes double to the display
  evo.drawDisplay();
  // Gets battery Level and write to display
  Serial.print("Battery Voltage: ");
  Serial.println(evo.getBattery());
  evo.writeToDisplay("Battery :", 0, 24);
  evo.writeToDisplay(evo.getBattery(), 60, 24);

  evo.drawDisplay(); // draws the display 

  // Plays the buzzer for 300ms
  evo.playTone(NOTE_G4, 300);

  //Sets the RGB LED to white (0-255)
  evo.setRGB(20, 20, 20);
  delay(1000);

}
void loop()
{
  // put your main code here, to run repeatedly:
  evo.setRGB(20, 0, 0);
  delay(1000);
  evo.setRGB(0, 20, 0);
  delay(1000);
  evo.setRGB(0, 0, 20);
  delay(1000);
}
