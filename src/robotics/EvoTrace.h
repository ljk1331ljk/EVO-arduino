#ifndef EVO_TRACE_H
#define EVO_TRACE_H

#include "../sensors/EvoTCS34725.h"
#include "../motors/EvoMotor.h"

enum TraceMode
{
    LEFT_FOLLOWER = 1,
    LEFT_INVERTER = 2,
    BOTH_FOLLOWER = 3,
    RIGHT_FOLLOWER = 4,
    RIGHT_INVERTER = 5
};

/**
 * @class EvoTrace
 * @brief A class to control tracing behavior using two color sensors and two motors.
 */
class EvoTrace
{
public:
    /**
     * @brief Constructor to initialize the EvoTrace object.
     * @param leftSensor Pointer to the left color sensor.
     * @param rightSensor Pointer to the right color sensor.
     * @param leftMotor Pointer to the left motor.
     * @param rightMotor Pointer to the right motor.
     */
    EvoTrace(EvoTCS34725 *leftSensor, EvoTCS34725 *rightSensor, EvoMotor *leftMotor, EvoMotor *rightMotor);

    /**
     * @brief Initializes the sensors and motors.
     */
    void begin();

    /**
     * @brief Starts the PD tracking behavior.
     * @param speed The speed of the motors.
     * @param kp The proportional gain.
     * @param kd The derivative gain.
     * @param mode The mode of operation.
     * @param ThV The threshold value.
     */
    void PDTrackOn(int speed, float kp, float kd, TraceMode mode, int ThV);

    /**
     * @brief Tracks a specified number of degrees.
     * @param speed The speed of the motors.
     * @param kp The proportional gain.
     * @param kd The derivative gain.
     * @param degrees The number of degrees to track.
     * @param mode The mode of operation (default: BOTH_FOLLOWER).
     * @param Thv The threshold value (default: 0).
     * @param brake Whether to brake at the end of tracking (default: true).
     */
    void PDTrackDegrees(int speed, float kp, float kd, int degrees, TraceMode mode = BOTH_FOLLOWER, int Thv = 0, bool brake = true);

    /**
     * @brief Tracks junctions based on sensor readings.
     * @param speed The speed of the motors.
     * @param kp The proportional gain.
     * @param kd The derivative gain.
     * @param threshold The threshold value for junction detection.
     * @param maxJunctions The maximum number of junctions to track.
     * @param mode The mode of operation (default: BOTH_FOLLOWER).
     * @param Thv The threshold value (default: 0).
     * @param brake Whether to brake at the end of tracking (default: true).
     */
    void PDTrackJunction(int speed, float kp, float kd, int threshold, int maxJunctions, TraceMode mode = BOTH_FOLLOWER, int Thv = 0, bool brake = true);

private:
    EvoTCS34725 *_leftSensor;  ///< Pointer to the left color sensor.
    EvoTCS34725 *_rightSensor; ///< Pointer to the right color sensor.
    EvoMotor *_leftMotor;      ///< Pointer to the left motor.
    EvoMotor *_rightMotor;     ///< Pointer to the right motor.

    uint16_t lr, lg, lb, lc; ///< Raw sensor values for the left sensor.
    uint16_t rr, rg, rb, rc; ///< Raw sensor values for the right sensor.

    int error, prevError = 0; ///< Error values for PD control.
    float P, D;               ///< Proportional and derivative variables.
};

#endif