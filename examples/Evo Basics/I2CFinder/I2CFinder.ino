#include <Wire.h>
#define SDA 1
#define SCL 2

#define TCA 0x70
bool isConnected(TwoWire &wire, uint8_t address) {
  wire.beginTransmission(address);
  return (Wire.endTransmission() == 0);
}

void TCA9548A(TwoWire &wire, uint8_t bus) {
  wire.beginTransmission(0x70);  // TCA9548A address
  wire.write(1 << bus);          // send byte to select bus
  wire.endTransmission();
}
void findI2CDevice(TwoWire &wire, uint8_t channel) {
  TCA9548A(wire, channel);
  for (int i = 0; i < 255; i++) {
    if (isConnected(Wire, i)) {
      Serial.print("0x");
      Serial.print(i, HEX);
      Serial.print(", ");
    }
  }
}

void setup() {
  Serial.begin(115100);
  delay(1000);
  Serial.println("I2C Finder");
  Wire.begin(SDA, SCL);
  TCA9548A(Wire, 0);
  Serial.print("I2CA:");
  int count = 0;
  bool multiplex = false;
  if (isConnected(Wire, 0x70)) {
    multiplex = true;
  }
  for (int i = 0; i < 255; i++) {
    if (isConnected(Wire, i)) {
      Serial.print("0x");
      Serial.print(i, HEX);
      Serial.print(", ");
    }
  }
  Serial.println();
  if (multiplex) {
    for (int i = 0; i < 8; i++) {
      Serial.print("I2C");
      Serial.print(i);
      Serial.print(": ");
      findI2CDevice(Wire, i);
      Serial.println();
     
    }
  }
  Wire1.begin(12, 13);
  Serial.print("I2CB:");
  for (int i = 0; i < 255; i++) {
    if (isConnected(Wire1, i)) {
      Serial.print("0x");
      Serial.print(i, HEX);
      Serial.print(", ");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
