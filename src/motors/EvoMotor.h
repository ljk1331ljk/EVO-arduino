#ifndef EVOMOTOR_H
#define EVOMOTOR_H
#include "../helper/EvoPWMDriver.h"
#include "../helper/X1pins.h"
#include <ESP32Encoder.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct MotorPins
{
    uint8_t power1;
    uint8_t power2;
    uint8_t tach1;
    uint8_t tach2;
};

enum MotorType
{
    GENERICWITHENCODER,
    GENERISWITHOUTENCODER,
    EV3LargeMotor,
    EV3MediumMotor,
    GeekServoDCMotor,
    ITERMKS,
    ITERMKT,
    EVOMotor300,
    EVOMotor100
};

enum MotorPort
{
    M1 = 8,
    M2 = 10,
    M3 = 12,
    M4 = 14
};

enum MotorState
{
    RUN,
    TARGET,
    BRAKE,
    COAST,
    HOLD
};

class EvoMotor
{
private:
    // Motor parameters
    MotorType _motorType;
    MotorPort _motorPort;
    MotorPins _motorPins;

    int _maxSpd, _minSpd;
    bool _motorFlip, _encoderAvailable, _encoderFlip;
    int _countPerRevolution;

    // Motor runtime parameters
    MotorState _motorState = COAST, _motorStopState = BRAKE;
    int _stallTime, _stallCountThreshold;
    int _targetSpeed, _targetAngle = 0, _targetEncoder = 0;
    bool _completed, _stalled;
    float _kp, _ki, _kd;

    ESP32Encoder encoder;
    EvoPWMDriver &driver = EvoPWMDriver::getInstance();

    static void motorControlTask(void *parameter);
    void move(int speed);
    void setParameters(MotorPort motorPort, bool motorFlip, int maxSpd, int minSpd, float kp, float kd, bool encoderAvailable, int countPerRevolution = 0);

public:

    EvoMotor(MotorPort motorPort, MotorType motorType = GENERICWITHENCODER, bool motorFlip = false);

    void begin();
    
    void flipEncoderDirection(bool flip);

    void setSpeedLimit (int maxSpd, int minSpd);

    void getSpeedLimit (int *maxSpd, int *minSpd);

    void setEncoderAvailable(bool avail);

    bool isEncoderAvailable();

    void setCountPerRevolution(int countPerRevolution);

    int getCountPerRevolution();

    int getCount();

    void setCount(int count);

    void resetCount();

    int getAngle();

    void setAngle(int degrees);

    void resetAngle();

    bool isStalled();

    void setStallThresholds(int timems, int angle);

    void setStopBehaviour(MotorState motorStopState);

    void stop();

    void hold();

    void coast();

    void brake();

    void run(int speed);

    void runCount(int speed, int count);

    void runAngle(int speed, int degrees);

    void runTime(int speed, int timeMS);

    void runTarget(int speed, int degrees, bool blocking = false);

    void runUntilStalled(int speed);

    void setPID(float kp, float ki, float kd);

    void getPID(float *kp, float *ki, float *kd);
};

#endif