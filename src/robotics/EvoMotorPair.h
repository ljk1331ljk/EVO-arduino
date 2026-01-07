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
     * @brief Sets the proportional-derivative (PD) control parameters for the motor pairing.
     * @param kp The proportional gain.
     * @param ki The integral gain.
     * @param kd The derivative gain.
     */
    void setPID(float kp, float ki, float kd);

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

    // /**
    //  * @brief Moves the motors following a Condition with the IMU.
    //  * @param leftSpeed Speed for the left motor.
    //  * @param rightSpeed Speed for the right motor.
    //  * @param Condition Condition with the IMU.
    //  * @param IMUkp The proportional gain.
    //  * @param IMUkd The derivative gain.
    //  * @param brake Whether to brake at the end of movement (default: true).
    //  */
    // void moveIMU(int leftSpeed, int rightSpeed, int Condition, float IMUkp = 0, float IMUkd = 0, bool brake = true);

    /**
     * @brief Performs a spot turn to a specific heading using the IMU.
     * @param speed The speed of the turn.
     * @param heading The target heading angle.
     * @param decelHeading The heading angle to start deceleration.
     * @param stopBehaviour The stopping behavior after movement (HOLD, BRAKE, or COAST).
     */
    void spotTurnIMU(int moveSpeed, float heading, float decelHeading, MotorStop stopBehaviour);

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