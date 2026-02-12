#ifndef EVO_HC05_H
#define EVO_HC05_H

#include <Arduino.h>
#include "SoftwareSerial/SoftwareSerial.h"
#include "X1pins.h"

enum HC05Mode
{
    ATMODE,
    BLMODE
};
class EvoHC05
{
private:
    SoftwareSerial _sw;
    HC05Mode _mode;
    int _pwr = HC05_PWR, _reset = HC05_RESET;
    bool waitResponse(const char *c);

public:
    EvoHC05();
    void begin();
    void setMode(HC05Mode mode, int baud = 38400);
    bool factorySettings();
    bool setName(const char *newName);
    void resetDevice();
    bool setBaud(int baud = 115200);
    bool checkResponse();
};

#endif