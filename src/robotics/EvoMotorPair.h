#ifndef EVO_MOTORPAIR_H
#define EVO_MOTORPAIR_H

#include "../motors/EvoMotor.h"
#include "../sensors/EvoBNO055.h"

/**
 * @class EvoMotorPair
 * @brief A class to control a pair of EvoMotors synchronously.
 */
class EvoMotorPair
{
private:
    EvoMotor *_m1;
    EvoMotor *_m2;
    EvoBNO055 *_imu;
    bool _imuAvailable = false, _useImu = false;
    int _minSpeed = 800, _accelDeg = 2000, _decelDeg = 2000;
    float _accel = 8, _decel = 8;
    float _kpSync = 20, _kdSync = 200;

public:
    /**
     * @brief Constructor to initialize a motor pair.
     * @param m1 Pointer to the first EvoMotor.
     * @param m2 Pointer to the second EvoMotor.
     */
    EvoMotorPair(EvoMotor *m1, EvoMotor *m2);

    /**
     * @brief Sets the minimum speed for the motors.
     * @param minSpeed The minimum speed value.
     */
    void setMinimumSpeed(int minSpeed);

    /**
     * @brief Sets the acceleration parameters.
     * @param accel The acceleration factor.
     * @param accelDeg The number of degrees over which acceleration occurs.
     */
    void setAcceleration(float accel, int accelDeg);

    /**
     * @brief Gets the current acceleration parameters.
     * @param accel Reference to store the acceleration factor.
     * @param accelDeg Reference to store the number of degrees for acceleration.
     */
    void getAcceleration(float &accel, int &accelDeg);

    /**
     * @brief Sets the deceleration parameters.
     * @param decel The deceleration factor.
     * @param decelDeg The number of degrees over which deceleration occurs.
     */
    void setDeceleration(float decel, int decelDeg);

    /**
     * @brief Gets the current deceleration parameters.
     * @param decel Reference to store the deceleration factor.
     * @param decelDeg Reference to store the number of degrees for deceleration.
     */
    void getDeceleration(float &decel, int &decelDeg);

    /**
     * @brief Sets the proportional-derivative (PD) control parameters for the motor pairing.
     * @param kp The proportional gain.
     * @param kd The derivative gain.
     */
    void setPD(float kp, float kd);

    /**
     * @brief Moves the motors at the specified speeds.
     * @param leftSpeed Speed for the left motor.
     * @param rightSpeed Speed for the right motor.
     */
    void move(int leftSpeed, int rightSpeed);

    /**
     * @brief Moves the motors a specified number of degrees.
     * @param leftSpeed Speed for the left motor.
     * @param rightSpeed Speed for the right motor.
     * @param degrees The number of degrees to move.
     * @param brake Whether to brake at the end of movement (default: true).
     */
    void moveDegrees(int leftSpeed, int rightSpeed, int degrees, bool brake = true);

    /**
     * @brief Moves the motors for a specified duration.
     * @param leftSpeed Speed for the left motor.
     * @param rightSpeed Speed for the right motor.
     * @param timems Duration in milliseconds.
     * @param brake Whether to brake at the end of movement (default: true).
     */
    void moveTime(int leftSpeed, int rightSpeed, int timems, bool brake = true);

    /**
     * @brief Applies braking to both motors.
     */
    void brake();

    /**
     * @brief Coasts both motors to a stop.
     */
    void coast();

    /**
     * @brief Resets both motor angles to zero.
     */
    void resetAngle();
};
#endif
