#ifndef EVO_HC05_H
#define EVO_HC05_H

#include <Arduino.h>
#include "SoftwareSerial/SoftwareSerial.h"
#include "../controllers/SelectedController.h"

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
    int _pwr = -1, _reset = -1, _rx = -1, _tx = -1;
    bool _available = false;
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
