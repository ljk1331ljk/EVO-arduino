#include <Evo.h>
#include <EvoServo.h>
EVO evo;
EvoServo s(SERVO1);
void setup() {
  Serial.begin(115200);
  evo.begin();
    evo.writeToDisplay("Servo Test", 0, 0, true, true);
  s.begin();
 
  //s.setPWM(0, 0); 
  for(int i=0; i< 4096 ; i+=10){
    s.setPWM(0, i);
    Serial.println(i);
    delay(300);
  }
   
  
}

void loop() {
}
