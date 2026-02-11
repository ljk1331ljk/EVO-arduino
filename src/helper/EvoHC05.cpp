#include "EvoHC05.h"

EvoHC05::EvoHC05()
{
    this->_mode = BLMODE;
}

void EvoHC05::begin()
{
    pinMode(this->_pwr, OUTPUT);
    pinMode(this->_reset, OUTPUT);
    _sw.begin(2400, SWSERIAL_8N1, 44, 43);
}

void EvoHC05::setMode(HC05Mode mode, int baud)
{
    if (this->_mode != mode)
    {
        if (mode == ATMODE)
        {
            digitalWrite(this->_pwr, HIGH);
            digitalWrite(this->_reset, HIGH);
            delay(2000);
            digitalWrite(this->_pwr, LOW);
            delay(2000); // minimum : 700ms
            digitalWrite(this->_reset, LOW);
            _sw.begin(38400, SWSERIAL_8N1, 44, 43);
            this->_mode = ATMODE;
        }
        else if (mode == BLMODE)
        {
            digitalWrite(this->_pwr, HIGH);
            delay(200);
            digitalWrite(this->_pwr, LOW);
            _sw.begin(baud, SWSERIAL_8N1, 44, 43);
            this->_mode = BLMODE;
        }
    }
}

// AT Mode functions

bool EvoHC05::waitResponse(const char *c)
{
    if (this->_mode == ATMODE)
    {
        String input = _sw.readString();
        char *str = (char *)input.c_str();
        int len = input.length();
        if (input.indexOf(c) >= 0)
        {
            return true;
        }
    }
    return false;
}

bool EvoHC05::factorySettings()
{
    if (this->_mode == ATMODE)
    {
        _sw.write("AT+ORGL\r\n");
        if (!this->waitResponse("OK"))
        {
            Serial.println("ERROR");
            return false;
        }
        this->_mode = BLMODE;
        return true;
    }
    return false;
}

bool EvoHC05::setName(const char *newName)
{
    if (this->_mode == ATMODE)
    {
        const char *prefix = "AT+NAME=";
        int totalLength = strlen(prefix) + strlen(newName) + 2; // +1 for the null terminator
        char *result = new char[totalLength];
        strcpy(result, prefix);
        strcat(result, newName);
        strcat(result, "\r\n");
        _sw.write(result);
        Serial.println(result);
        if (!this->waitResponse("OK"))
        {
            Serial.println("ERROR");
            return false;
        }
        return true;
    }
    return false;
}

void EvoHC05::resetDevice()
{
    if (this->_mode == ATMODE)
    {
        Serial.println("AT+RESET");
        _sw.write("AT+RESET");
        digitalWrite(this->_pwr, HIGH);
        delay(200);
        digitalWrite(this->_pwr, LOW);
        this->_mode = BLMODE;
    }
}

bool EvoHC05::setBaud(int baud)
{
    if (this->_mode == ATMODE)
    {
        if (baud == 9600)
        {
            _sw.write("AT+UART=9600,0,0\r\n");
        }
        else if (baud == 38400)
        {
            _sw.write("AT+UART=38400,0,0\r\n");
        }
        else if (baud == 57600)
        {
            _sw.write("AT+UART=57600,0,0\r\n");
        }
        else if (baud == 115200)
        {
            _sw.write("AT+UART=115200,0,0\r\n");
        }
        else if (baud == 921600)
        {
            _sw.write("AT+UART=921600,0,0\r\n");
        }
        else
        {
            Serial.println("Baud rate not supported.");
            return false;
        }
        if (!this->waitResponse("OK"))
        {
            Serial.println("ERROR");
            return false;
        }
        return true;
    }
    return true;
}

bool EvoHC05::checkResponse()
{
    if (this->_mode == ATMODE)
    {
        _sw.write("AT\r\n");
        return this->waitResponse("OK");
    }
    return false;
}
