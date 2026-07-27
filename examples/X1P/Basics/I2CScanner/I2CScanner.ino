#include <Evo.h>

EvoX1P evo;

void showChannel(uint8_t channel)
{
  constexpr int maxAddresses = 5;
  uint8_t addresses[maxAddresses];
  int addressCount = evo.scanI2CChannel(
      static_cast<I2CChannel>(channel), addresses, maxAddresses);

  char line[22];
  evo.clearDisplay();
  snprintf(line, sizeof(line), "I2C channel %u", channel + 1);
  evo.writeLineToDisplay(line, 0);

  if (addressCount == 0)
  {
    evo.writeLineToDisplay("No devices found", 2);
  }
  else
  {
    for (int i = 0; i < addressCount; ++i)
    {
      snprintf(line, sizeof(line), "%d: 0x%02X", i + 1, addresses[i]);
      evo.writeLineToDisplay(line, i + 2);
    }
  }
  evo.drawDisplay();
}

void setup()
{
  evo.begin();
  evo.setFontSize(8);
}

void loop()
{
  for (uint8_t channel = 0; channel < evo.getI2CChannelCount(); ++channel)
  {
    showChannel(channel);
    delay(2000);
  }
}
