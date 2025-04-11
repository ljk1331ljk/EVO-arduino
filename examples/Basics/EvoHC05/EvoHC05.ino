#include <Evo.h>

#define DEVICE_NAME "EVOX1E-1" // Change this to your device name
EVOX1 evo;
EvoHC05 hc;

void setup()
{
  Serial.begin(115200);
  evo.begin();
  hc.begin();
  evo.flipDisplayOrientation();

  hc.setMode(ATMODE);
  evo.writeLineToDisplay("AT Mode set", 0, true, true);
  delay(1000);

  while (!hc.checkResponse())
  {
    evo.writeLineToDisplay("checking response", 0, true, true);
    delay(1000);
  }
  evo.writeLineToDisplay("Response available", 0, true, true);
  delay(1000);

  if (hc.factorySettings())
  {
    evo.writeLineToDisplay("Factory settings set", 0, true, true);
  }
  else
  {
    evo.writeLineToDisplay("Factory settings not set", 0, true, true);
  }
  delay(1000);

  hc.setMode(ATMODE);
  evo.writeLineToDisplay("AT Mode set", 0, true, true);
  delay(1000);

  while (!hc.checkResponse())
  {
    evo.writeLineToDisplay("checking response", 0, true, true);
    delay(1000);
  }

  if (hc.setName(DEVICE_NAME))
  {
    evo.writeLineToDisplay("Name set", 0, true, true);
  }
  else
  {
    evo.writeLineToDisplay("Name not set", 0, true, true);
  }
  delay(1000);

  if (hc.setBaud())
  {
    evo.writeLineToDisplay("Baudrate set", 0, true, true);
  }
  else
  {
    evo.writeLineToDisplay("Baudrate not set", 0, true, true);
  }
  delay(1000);

  hc.setMode(BLMODE);
  evo.writeLineToDisplay("BL Mode set", 0, true, true);
  delay(1000);

  evo.writeLineToDisplay("Bluetooth is setup", 0, true, true);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
