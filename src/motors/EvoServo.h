/**
 * @file EvoServo.h
 * @brief Class for controlling servo motors using the EvoPWMDriver.
 */

#ifndef EVO_SERVO_H
#define EVO_SERVO_H

#include "../helper/EvoPWMDriver.h"

/**
 * @enum ServoType
 * @brief Enumeration of different servo motor types.
 */
enum ServoType
{
    Default,
    SG90,
    GeekServo360Grey,    // Grey
    GeekServo360Orange,  // Orange
    GeekServoContinuous, // Green
};

/**
 * @enum ServoChannel
 * @brief Enumeration of servo channels on the multiplexer.
 */
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

/**
 * @class EvoServo
 * @brief Class to control a servo motor using the EvoPWMDriver.
 */
class EvoServo
{

public:
    /**
     * @brief Constructs an EvoServo object.
     * @param servoChannel The servo channel to use.
     * @param servoType The type of servo motor (default is Default).
     */
    EvoServo(ServoChannel servoChannel, ServoType servoType = Default);

    /**
     * @brief Initializes the servo motor.
     */
    void begin();

    /**
     * @brief Sets the pulse width range for the servo.
     * @param minPulse Minimum pulse width.
     * @param maxPulse Maximum pulse width.
     */
    void setPulse(int minPulse, int maxPulse);

    /**
     * @brief Sets the rotation range of the servo.
     * @param minRange Minimum angle (in degrees).
     * @param maxRange Maximum angle (in degrees).
     */
    void setRange(int minRange, int maxRange);

    /**
     * @brief Moves the servo to a specific position.
     * @param position Target position (in degrees).
     */
    void write(int position);

    /**
     * @brief Sets the PWM signal for the servo.
     * @param on Start time of the pulse.
     * @param off End time of the pulse.
     */
    void setPWM(int on, int off);

private:
    EvoPWMDriver &driver = EvoPWMDriver::getInstance(); /**< Reference to the singleton PWM driver */
    uint8_t _servoChannel;                              /**< The assigned servo channel */
    int _minPulse = 300;                                /**< Minimum pulse width */
    int _maxPulse = 1100;                               /**< Maximum pulse width */
    int _minRange = 0;                                  /**< Minimum servo angle */
    int _maxRange = 180;                                /**< Maximum servo angle */
};
#endif