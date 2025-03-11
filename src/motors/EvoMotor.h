/**
 * @file EvoMotor.h
 * @brief Class for controlling various types of motors with encoders using the EvoPWMDriver.
 */

#ifndef EVOMOTOR_H
#define EVOMOTOR_H
#include "../helper/EvoPWMDriver.h"
#include "../helper/X1pins.h"
#include <ESP32Encoder.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/**
 * @struct MotorPins
 * @brief Structure to store motor pin configurations.
 */
struct MotorPins
{
    uint8_t power1; /**< PWM power pin 1 */
    uint8_t power2; /**< PWM power pin 2 */
    uint8_t tach1;  /**< Encoder signal pin 1 */
    uint8_t tach2;  /**< Encoder signal pin 2 */
};

/**
 * @enum MotorType
 * @brief Enumeration of different motor types supported.
 */
enum MotorType
{
    GENERICWITHENCODER,    /**< Generic motor with encoder */
    GENERICWITHOUTENCODER, /**< Generic motor without encoder */
    EV3LargeMotor,         /**< EV3 Large Motor */
    EV3MediumMotor,        /**< EV3 Medium Motor */
    GeekServoDCMotor,      /**< GeekServo DC Motor */
    ITERMKS,               /**< ITER Speed motor */
    ITERMKT,               /**< ITER Torque motor */
    EVOMotor300,           /**< EVO Motor 300 */
    EVOMotor100            /**< EVO Motor 100 */
};

/**
 * @enum MotorPort
 * @brief Enumeration of available motor ports.
 */
enum MotorPort
{
    M1 = 8,
    M2 = 10,
    M3 = 12,
    M4 = 14
};

/**
 * @enum MotorStop
 * @brief Enumeration of motor states.
 */
enum MotorStop
{
    BRAKE, /**< Motor is braking */
    COAST, /**< Motor is coasting */
    HOLD   /**< Motor is holding position */
};

/**
 * @class EvoMotor
 * @brief Class to control a motor using EvoPWMDriver and an encoder.
 */
class EvoMotor
{
private:
    enum runMode
    {
        NONE,
        TIME,
        COUNT,
        ANGLE,
        TARGET,
        HOLDPOS,
        STALLED,
    } _runMode = runMode::NONE;

    MotorType _motorType;
    MotorPort _motorPort;
    MotorPins _motorPins;

    int _maxSpd, _minSpd;
    bool _motorFlip, _encoderAvailable;
    int _countPerRevolution;

    // Motor runtime parameters
    MotorStop _motorState = COAST, _motorStopBehaviour = BRAKE;
    uint16_t _holdPower = 2000;
    int _stallThreshold;
    int _targetValue, _targetSpeed, _targetThen, _targetEncoder = 0;
    int _measuredSpeed;
    float _kp = 2000, _kd = 5000;

    ESP32Encoder encoder;
    EvoPWMDriver &driver = EvoPWMDriver::getInstance();
    TaskHandle_t motorTaskHandle = NULL;
    bool motorTaskSuspended;
    void pauseMotorTask();
    void resumeMotorTask();
    static void motorControlTask(void *parameter);
    static void motorSpeedTask(void *parameter);
    void move(int speed);
    void setParameters(MotorPort motorPort, bool motorFlip, int maxSpd, int minSpd, float kp, float kd, bool encoderAvailable, int countPerRevolution = 0);

public:
    /**
     * @brief Constructor for EvoMotor.
     * @param motorPort The motor port.
     * @param motorType The type of motor.
     * @param motorFlip Whether the motor direction should be flipped.
     */
    EvoMotor(MotorPort motorPort, MotorType motorType = GENERICWITHENCODER, bool motorFlip = false);

    /**
     * @brief Initializes the motor.
     */
    void begin();

    /**
     * @brief Flips the direction of the encoder.
     * @param flip Whether the encoder direction should be flipped.
     */
    void flipEncoderDirection(bool flip);

    /**
     * @brief Sets the minimum and maximum speed of the motor.
     * @param maxSpd Maximum speed.
     * @param minSpd Minimum speed.
     */
    void setSpeedLimit(int maxSpd, int minSpd);

    /**
     * @brief Gets the speed limits.
     * @param maxSpd Pointer to store the maximum speed.
     * @param minSpd Pointer to store the minimum speed
     */
    void getSpeedLimit(int *maxSpd, int *minSpd);

    /**
     * @brief Sets encoder availability.
     */
    void setEncoderAvailable(bool avail);

    /**
     * @brief Checks if encoder is available.
     * @return True if encoder is available, false otherwise.
     */
    bool isEncoderAvailable();

    /**
     * @brief Sets encoder count per revolution.
     */
    void setCountPerRevolution(int countPerRevolution);

    /**
     * @brief Gets encoder count per revolution.
     * @return The count per revolution.
     */
    int getCountPerRevolution();

    /**
     * @brief Sets the encoder count.
     */
    void setCount(int count);

    /**
     * @brief Gets the encoder count.
     * @return The encoder count.
     */
    int getCount();

    /**
     * @brief Resets the encoder count.
     */
    void resetCount();

    /**
     * @brief Sets the current motor angle.
     */
    void setAngle(int degrees);

    /**
     * @brief Gets the current motor angle.
     * @return The angle in degrees.
     */
    int getAngle();

    /**
     * @brief Resets the motor angle.
     */
    void resetAngle();

    /**
     * @brief Checks if the motor is stalled.
     * @return True if stalled, false otherwise.
     */
    bool isStalled();

    /**
     * @brief Sets motor stall thresholds.
     */
    void setStallThreshold(int threshold);

    /**
     * @brief Sets motor stop behavior.
     */
    void setStopBehaviour(MotorStop motorStopState);

    /**
     * @brief Stops the motor based on the stop behaviour set using setStopBehaviour(MotorState motorStopState).
     */
    void stop();

    /**
     * @brief Holds the motor in its current position.
     */
    void hold();

    /**
     * @brief Set power used when holding
     * @param power power to hold (0-4096)
     */
    void setHoldPower(uint16_t power);

    /**
     * @brief Removes power from the motors.
     */
    void coast();

    /**
     * @brief Applys braking force on the motor to stop the motor.
     */
    void brake();

    /**
     * @brief Runs the motor at a specified speed.
     * @param speed Motor speed.
     */
    void run(int speed);

    /**
     * @brief Runs the motor for a specified encoder count.
     * @param speed Motor speed.
     * @param count Encoder count.
     * @param blocking Wait for action to be completed.
     */
    void runCount(int speed, int count, bool blocking = true);

    /**
     * @brief Runs the motor for a specified motor degree.
     * @param speed Motor speed.
     * @param degrees Motor degrees.
     * @param blocking Wait for action to be completed.
     */
    void runAngle(int speed, int degrees, bool blocking = true);

    /**
     * @brief Runs the motor for a specified time.
     * @param speed Motor speed.
     * @param timeMS Time in miliseconds.
     * @param blocking Wait for action to be completed.
     */
    void runTime(int speed, int timeMS, bool blocking = true);

    /**
     * @brief Runs the motor to a specified absolute position.
     * @param speed Motor speed.
     * @param degrees Motor absolute degree.
     * @param blocking Wait for action to be completed.
     */
    void runTarget(int speed, int angle, MotorStop then = MotorStop::HOLD, bool blocking = true);

    /**
     * @brief Sets PID control values for runTarget()
     * @param kp Proportional gain.
     * @param ki Integral gain.
     * @param kd Derivative gain.
     */
    void setTargetPD(float kp, float kd);

    /**
     * @brief Gets the PID control values for runTarget()
     * @param kp Pointer to store proportional gain.
     * @param ki Pointer to store integral gain.
     * @param kd Pointer to store derivative gain.
     */
    void getTargetPD(float *kp, float *kd);

    /**
     * @brief Runs the motor until it is stalled.
     * @param speed Motor speed.
     * @param blocking Wait for action to be completed.
     */
    void runUntilStalled(int speed, bool blocking = true);

    /**
     * @brief Gets the motor speed
     * @return speed in deg/s
     */
    int getSpeed();
};

#endif