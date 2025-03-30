class Programmer{
  private:
    int pwr, reset;
    bool mode;
    bool waitResponse(const char* c){
      String input = Serial0.readString();
      Serial.println(input);
      char *str = (char*) input.c_str();
      int len = input.length();
      for (size_t i = 0; i < len; i++){
        Serial.print(str[i], DEC);
        Serial.print(" ");
      }
      Serial.println();
      if (input.indexOf(c) >= 0) {
        return true;
      }
      return false;
    }
  public:
    Programmer(int pwr, int reset){
      this->pwr = pwr;
      this->reset = reset;
      this->mode = true;
      
    }
    void begin(){
      pinMode(this->pwr, OUTPUT);
      pinMode(this->reset, OUTPUT);
    }

    void ATMode(){
      digitalWrite(this->pwr, HIGH);
      digitalWrite(this->reset, HIGH);
      delay(2000);
      digitalWrite(this->pwr, LOW);
      delay(2000); //minimum : 700ms
      digitalWrite(this->reset, LOW);
      Serial0.begin(38400);
    }
    void factorySettings(){
      Serial.println("AT+ORGL");
      Serial0.write("AT+ORGL\r\n");
    }
    void BLMode(int baud){
      digitalWrite(this->pwr, HIGH);
      delay(200);
      digitalWrite(this->pwr, LOW);
      Serial0.begin(baud);
    }
    void setName(const char* newName){
      const char* prefix = "AT+NAME=";
      int totalLength = strlen(prefix) + strlen(newName) + 2; // +1 for the null terminator
      char* result = new char[totalLength];
      strcpy(result, prefix);
      strcat(result, newName);
      strcat(result, "\r\n");
      Serial0.write(result);
      Serial.println(result);
      if (!this->waitResponse("OK")){
        Serial.println("ERROR");
      }
    }
    void resetDevice(){
      Serial.println("AT+RESET");
      Serial0.write("AT+RESET");
      digitalWrite(this->pwr, HIGH);
      delay(200);
      digitalWrite(this->pwr, LOW);
    }
    void setBaud(const char* baud){
      const char* prefix = "AT+UART=";
      int totalLength = strlen(prefix) + strlen(baud) + 1; // +1 for the null terminator
      char* result = new char[totalLength];
      strcpy(result, prefix);
      strcat(result, baud);
      Serial.println(result);
      Serial0.write("AT+UART=115200,0,0\r\n");
      if (!this->waitResponse("OK")){
        Serial.println("ERROR");
      }
    }
    bool checkResponse(){
      Serial0.write("AT\r\n");
      return this->waitResponse("OK");
    }

};