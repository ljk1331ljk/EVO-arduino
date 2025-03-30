#ifndef EVO_HC05_H
#define EVO_HC05_H

enum HC05Mode{
    ATMODE,
    BLMODE
}
class EvoHC05{
    private:
        HC05Mode _mode;
        int _pwr = HC05_PWR, _reset = HC05_RESET;
        bool waitResponse(const char* c);
    
    public:
        EvoHC05();
        void begin();
        void setMode(HC05Mode mode, int baud = 38400);
        void factorySettings();
        void setName(const char* newName);
        void resetDevice();
        void setBaud(const char* baud);
        bool checkResponse();
}


#endif