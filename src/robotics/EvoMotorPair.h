#ifndef EVO_MOTORPAIR_H
#define EVO_MOTORPAIR_H

#include "../motors/EvoMotor.h"
#include "../sensors/EvoIMU.h"

/**
 * @class EvoMotorPair
 * @brief A class to control a pair of EvoMotors synchronously.
 */
class EvoMotorPair
{
private:
    EvoMotor *_m1;
    EvoMotor *_m2;
    EvoIMU *_imu;
    bool _imuAvailable = false, _useImu = false;
    int _startSpeed = 800, _endSpeed = 800, _accel = 10000, _decel = 10000;
    int _kpSync = 70, _kiSync = 5, _kdSync = 800;
    float _kpGyro = 70, _kiGyro = 10, _kdGyro = 1200;
    int _kpIMU = 10, _kdIMU = 50;
    MotorStop _stopBehavior = MotorStop::BRAKE;

public:
    /**
     * @brief Constructor to initialize a motor pair.
     * @param m1 Pointer to the first EvoMotor.
     * @param m2 Pointer to the second EvoMotor.
     * @param imu Pointer to the EvoBNO055 IMU sensor.
     */
    EvoMotorPair(EvoMotor *m1, EvoMotor *m2, EvoIMU *imu = nullptr);

    /**
     * @brief Sets the start speed for the motors.
     * @param startSpeed The minimum speed value.
     */
    void setStartSpeed(int startSpeed);

    /**
     * @brief Sets the end speed for the motors.
     * @param endSpeed The minimum speed value.
     */
    void setEndSpeed(int endSpeed);

    /**
     * @brief Sets the acceleration parameters.
     * @param accel The acceleration factor.
     */
    void setAcceleration(int accel);

    /**
     * @brief Gets the current acceleration parameters.
     * @param accel Reference to store the acceleration factor.
     * @return The acceleration factor.
     */
    int getAcceleration();

    /**
     * @brief Sets the deceleration parameters.
     * @param decel The deceleration factor.
     */
    void setDeceleration(int decel);

    /**
     * @brief Gets the current deceleration parameters.
     * @param decel Reference to store the deceleration factor.
     * @return The deceleration factor.
     */
    int getDeceleration();

    /**
     * @brief Sets the proportional-integral-derivative (PID) control parameters for the motor pairing.
     * @param kp The proportional gain.
     * @param ki The integral gain.
     * @param kd The derivative gain.
     */
    void setSyncPID(int kp, int ki, int kd);

    /**
     * @brief Sets the proportional-integral-derivative (PID) control parameters for the gyro.
     * @param kp The proportional gain.
     * @param ki The integral gain.
     * @param kd The derivative gain.
     */
    void setGyroPID(float kp, float ki, float kd);

    /**
     * @brief Sets the stopping behavior for the motors.
     * @param stopBehavior The stopping behavior (HOLD, BRAKE, or COAST).
     */
    void setStopBehavior(MotorStop stopBehavior);

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
     * @param stop The stopping behavior after movement (HOLD, BRAKE, or COAST) Default is hold.
     */
    void moveDegrees(int leftSpeed, int rightSpeed, int degrees);
    void moveDegrees(int leftSpeed, int rightSpeed, int degrees, MotorStop stopBehaviour);

    /**
     * @brief Moves the motors for a specified duration.
     * @param leftSpeed Speed for the left motor.
     * @param rightSpeed Speed for the right motor.
     * @param timems Duration in milliseconds.
     * @param stop The stopping behavior after movement (HOLD, BRAKE, or COAST) Default is hold.
     */
    void moveTime(int leftSpeed, int rightSpeed, int timems, int slowdowntime = 200, MotorStop stopBehaviour = MotorStop::HOLD);

    /**
     * @brief Moves the motors following a Condition with the IMU.
     * @param speed Speed for the motors.
     * @param degrees The number of degrees to move.
     * @param heading The target heading angle. If -1, the current heading is maintained.
     * @param stopBehaviour The stopping behavior after movement (HOLD, BRAKE, or COAST) Default is hold.
     */
    void StraightDegreesIMU(int motorSpeed, int degrees, int heading = -1, MotorStop stopBehaviour = MotorStop::HOLD);

    /**
     * @brief Performs a spot turn to a specific heading using the IMU.
     * @param speed The speed of the turn.
     * @param heading The target heading angle.
     * @param decelHeading The heading angle to start deceleration.
     * @param stopBehaviour The stopping behavior after movement (HOLD, BRAKE, or COAST).
     */
    void spotTurnGyro(int motorSpeed, float heading, bool reset = true, MotorStop stopBehaviour = MotorStop::HOLD);

    /**
     * @brief Stops both motors based on the stop behavior.
     */
    void stop();

    /**
     * @brief Applies braking to both motors.
     */
    void brake();

    /**
     * @brief Coasts both motors to a stop.
     */
    void coast();

    /**
     * @brief Holds the current position of both motors.
     */
    void hold();

    /**
     * @brief Resets both motor angles to zero.
     */
    void resetAngle();
};
#endif