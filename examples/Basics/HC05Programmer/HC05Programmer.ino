#include "Programmer.h"

#define HC05_PWR 45
#define HC05_RESET 46

Programmer hc05(HC05_PWR, HC05_RESET);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Program begin");
  Serial0.begin(38400);

  
  delay(1000);
  Serial.println("setting HC05 pins");
  hc05.begin();
  
  Serial.println("putting in AT mode");
  hc05.ATMode();
  Serial.println("atmode set");
  
  while(!hc05.checkResponse()){
    Serial.println("Waiting for response...");
    delay(1000);
  }

  // hc05.factorySettings();
  
  while(!hc05.checkResponse()){
    Serial.println("Waiting for response...");
    delay(1000);
  }
  delay(3000);
  hc05.setName("EVOX1E-1");
  Serial.println("name set");
  delay(3000);
  hc05.setBaud("115200,0,0");
  Serial.println("baudrate set");
  delay(3000);
  hc05.resetDevice();
  Serial.println("reset hc05");
  hc05.BLMode(115200);
  Serial0.begin(115200);
}

void loop() {
  if (Serial.available()){
    // Serial.write(Serial.read());
    Serial0.write(Serial.read());
    
  }
  if (Serial0.available()){
    // Serial.println("S:");
    Serial.write(Serial0.read());
  }
}
