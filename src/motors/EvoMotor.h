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
    COAST
};

class EvoMotor
{
private:
    MotorPort _motorPort;
    bool _motorFlip;
    int targetSpeed;
    bool completed;
    float _kp = 5, _kd = 30;
    int targetAngle = 0;
    MotorPins motorPins;
    MotorState motorState = COAST;
    int targetEncoder = 0;
    ESP32Encoder encoder;
    static void motorControlTask(void *parameter);
    void move(int speed);
    EvoPWMDriver &driver = EvoPWMDriver::getInstance();

public:
    // Constructor with port and positive direction
    EvoMotor(MotorPort motorPort, bool motorFlip = false);

    void begin();

    // Method to get current angle
    int getAngle();

    void setAngle(int angle);

    // Method to reset angle
    void resetAngle();

    // Method to stop the motor
    void coast();

    // Method to brake the motor
    void brake();

    // Method to run the motor at a specified speed
    void run(int speed);

    // Method to run the motor for a specified number of degrees
    void runDegrees(int speed, int degrees);

    void runTarget(int speed, int degrees, bool blocking = false);

    void setPID(float kp, float kd);
};

#endif