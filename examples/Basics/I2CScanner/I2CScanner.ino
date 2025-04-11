#include <Evo.h>

EVOX1 evo;

void setup()
{
  evo.begin();
  Serial.begin(115200);
  while (!Serial) // Waits for serial to be connected
    ;
  Serial.println("I2C Scanner");
  delay(1000);
  Serial.println("0x70 is the address of the multiplexor. It will show up on every I2C port.");

  int maxAddresses = 5;
  int numAddress = 0;
  uint8_t i2CAddress[maxAddresses];
  for (int i = 0; i < 8; i++)
  {
    numAddress = evo.scanI2CChannel((I2CChannel)i, i2CAddress, maxAddresses);
    if (numAddress != 0)
    {
      Serial.printf("%d addresse(s) found on I2C%d:", numAddress, i + 1);
      for (int j = 0; j < numAddress; j++)
      {
        Serial.printf(" 0x%x", i2CAddress[j]);
      }
      Serial.println();
    }
  }
}

void loop()
{
  delay(1000);
}
