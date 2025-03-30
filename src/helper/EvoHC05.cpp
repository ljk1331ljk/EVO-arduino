#include "EvoHC05.h"

EvoHC05::EvoHC05()
  this->_mode = BLMODE;
}

void EvoHC05::begin(){
  pinMode(this->_pwr, OUTPUT);
  pinMode(this->_reset, OUTPUT);
}

void EvoHC05::setMode(HC05Mode mode, int baud){
    if (this->_mode != mode){
        if (mode == ATMODE){
            digitalWrite(this->pwr, HIGH);
            digitalWrite(this->reset, HIGH);
            delay(2000);
            digitalWrite(this->pwr, LOW);
            delay(2000); //minimum : 700ms
            digitalWrite(this->reset, LOW);
            Serial0.begin(38400);
            this->mode = ATMODE;
        }
        else if (mode == BLMODE){
            digitalWrite(this->pwr, HIGH);
            delay(200);
            digitalWrite(this->pwr, LOW);
            Serial0.begin(baud);
        }    
    }
}

//AT Mode functions

bool EvoHC05::waitResponse(const char* c){
    if (this->mode == ATMODE){
        String input = Serial0.readString();
        Serial.println(input);
        char *str = (char*) input.c_str();
        int len = input.length();
        // for (size_t i = 0; i < len; i++){
        //     Serial.print(str[i], DEC);
        //     Serial.print(" ");
        // }
        // Serial.println();
        if (input.indexOf(c) >= 0) {
            return true;
        }
    }
  return false;
}

void EvoHC05::factorySettings(){
    if (this->mode == ATMODE){
        Serial.println("AT+ORGL");
        Serial0.write("AT+ORGL\r\n");
    }
}

void EvoHC05::setName(const char* newName){
    if (this->mode == ATMODE){
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
}

void EvoHC05::resetDevice(){
    if (this->mode == ATMODE){    
        Serial.println("AT+RESET");
        Serial0.write("AT+RESET");
        digitalWrite(this->pwr, HIGH);
        delay(200);
        digitalWrite(this->pwr, LOW);
        this->mode = BLMODE;
    }
}

void EvoHC05::setBaud(const char* baud){
    if (this->mode == ATMODE){
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
}

bool EvoHC05::checkResponse(){
    if (this->mode == ATMODE){
        Serial0.write("AT\r\n");
        return this->waitResponse("OK");
    }
    return false;
}
