#ifndef EVO_SERVO_H
#define EVO_SERVO_H

#include "../helper/EvoPWMDriver.h"

enum ServoType
{
    Default,
    SG90,
    GeekServo360Grey,    // Grey
    GeekServo360Orange,  // Orange
    GeekServoContinuous, // Green

};

enum ServoChannel
{
    SERVOUNDEFINED = -1,
    SERVO1 = 0, // Channel 0 on the multiplexer
    SERVO2 = 1, // Channel 1 on the multiplexer
    SERVO3 = 2, // Channel 2 on the multiplexer
    SERVO4 = 3, // Channel 3 on the multiplexer
    SERVO5 = 4, // Channel 4 on the multiplexer
    SERVO6 = 5, // Channel 5 on the multiplexer
    SERVO7 = 6, // Channel 6 on the multiplexer
    SERVO8 = 7  // Channel 7 on the multiplexer
};

class EvoServo
{

public:
    EvoServo(ServoChannel servoChannel, ServoType servoType = Default)
    {
        _servoChannel = static_cast<uint8_t>(servoChannel);
        switch (servoType)
        {
        case SG90:
            setPulse(300, 1200);
            setRange(0, 180);
            break;
        case GeekServo360Grey:
            setPulse(200, 980);
            setRange(0, 360);
            break;
        case GeekServo360Orange:
            setPulse(200, 980);
            setRange(0, 360);
            break;
        case GeekServoContinuous:
            setPulse(180, 1040);
            setRange(-100, 100);
            break;
        case Default:
            setPulse(300, 1200);
            setRange(0, 180);
            break;
        }
    }
    void begin();
    void setPulse(int minPulse, int maxPulse);
    void setRange(int minRange, int maxRange);
    void write(int position);
    void setPWM(int on, int off);

private:
    EvoPWMDriver &driver = EvoPWMDriver::getInstance();
    uint8_t _servoChannel;
    int _minPulse = 300, _maxPulse = 1100;
    int _minRange = 0, _maxRange = 180;
};
#endif