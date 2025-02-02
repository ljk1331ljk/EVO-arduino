#ifndef EVOMOTOR_H
#define EVOMOTOR_H
#include "../helper/EvoPWMDriver.h "
#include "../helper/X1pins.h "
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
    ITERSpeed,
    ITERTorque
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

    int _minSpeed, _maxSpeed;
    bool _motorFlip, _encoderAvailable;
    int _countPerRevolution;

    // Motor runtime parameters
    MotorState _motorState = COAST, _motorStopState = COAST;
    int _stallTime, _stallCountThreshold;
    int _targetSpeed, _targetAngle = 0, _targetEncoder = 0;
    bool _completed, _stalled;
    float _kp = 5, _ki = 0.1, _kd = 30;

    ESP32Encoder encoder;
    EvoPWMDriver &driver = EvoPWMDriver::getInstance();

    static void motorControlTask(void *parameter);
    void move(int speed);
    void setParameters(MotorPort motorPort, bool motorFlip, int minSpeed, int maxSpeed, bool encoderAvailable, int countPerRevolution = 0, float kp = 0, float ki = 0, float kd = 0);

public:
    // Constructor with port and positive direction
    EvoMotor(MotorPort motorPort, MotorType motorType = GENERICWITHENCODER, bool motorFlip = false);

    // Initialises the motor parameters
    void begin();

    // Method to set the minimum and maximum speed of the motor
    void setSpeedLimit(int minSpeed, int maxSpeed);

    // Method to get the minimum and maximum speed of the motor
    void getSpeedLimit(int *minSpeed, int *maxSpeed);

    // Method to set encoder availability
    void setEncoderAvailable(bool avail);

    // Method to get encoder availability
    bool isEncoderAvailable();

    // Method to set encoder count per revolution
    void setCountPerRevolution(int countPerRevolution);

    // Method to get encoder count per revolution
    int getCountPerRevolution();

    // Method to get the encoder count
    int getCount();

    // Method to set the encoder count
    void setCount(int count);

    // Method to reset the encoder count
    void resetCount();

    // Method to get current degrees
    int getAngle();

    // Method to set current degrees
    void setAngle(int degrees);

    // Method to reset angle
    void resetAngle();

    // Method returns if the motor is stalled
    bool stalled();

    // Method to set the motor stall thersholds
    void setStallThresholds(int timems, int count);

    // Method to stop the motor
    void setStopBehaviour(MotorState motorStopState);

    // Method to stop the motor using motorStopState
    void stop();

    // Method to hold the motor at a specified position
    void hold();

    // Method to coast the motor
    void coast();

    // Method to brake the motor
    void brake();

    // Method to run the motor at a specified speed
    void run(int speed);

    void runCount(int speed, int count, bool wait);

    // Method to run the motor for a specified number of degrees
    void runAngle(int speed, int degrees);

    // Method to run the motor for a specified amount of time
    void runTime(int speed, int timeMS);

    // Method to run the motor to a specified potision
    void runTarget(int speed, int degrees, bool blocking = false);

    // Method to run the motor until it is stalled
    void runUntilStalled(int speed);

    void setPID(float kp, float ki, float kd);

    void getPID(float *kp, float *ki, float *kd);
};

#endif