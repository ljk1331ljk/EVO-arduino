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
    int _wheelDiameter = 46, _axleTrack = 104;              // in mm
    float _gyroEncoderFactor = _wheelDiameter / _axleTrack; // in mm

public:
    /**
     * @brief Constructor to initialize a motor pair.
     * @param m1 Pointer to the first EvoMotor.
     * @param m2 Pointer to the second EvoMotor.
     * @param wheelDiameter The diameter of the wheels in mm (default: 46).
     * @param axleTrack The distance between the wheels in mm (default: 104).
     * @param imu Pointer to IMU
     */
    EvoMotorPair(EvoMotor *m1, EvoMotor *m2, int wheelDiameter = 46, int axleTrack = 104, EvoBNO055 *IMU = NULL);

    /**
     * @brief Sets the wheel diameter and axle track for the motors.
     * @param wheelDiameter The diameter of the wheels in mm.
     * @param axleTrack The distance between the wheels in mm.
     */
    void setWheelDiameter(int wheelDiameter, int axleTrack);

    /**
     * @brief Gets the wheel diameter and axle track for the motors.
     * @param wheelDiameter Pointer to store the diameter of the wheels in mm.
     * @param axleTrack Pointer to store the distance between the wheels in mm.
     */
    void getWheelDiameter(int *wheelDiameter, int *axleTrack);

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
     * @brief Sets the deceleration parameters.
     * @param decel The deceleration factor.
     * @param decelDeg The number of degrees over which deceleration occurs.
     */
    void setDeceleration(float decel, int decelDeg);

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

    /**
     * @brief Gets the current motor angle.
     * @return The angle in degrees.
     */
    int getAngle();

    /**
     * @brief Checks if the IMU is available.
     * @return True if IMU is available, false otherwise.
     */
    bool imuAvailable();

    /**
     * @brief Sets the use of IMU for movement.
     * @param useIMU  Whether to use IMU (default: true).
     */
    void useIMU(bool useImu = true);

    /**
     * @brief Moves the motors in a straight line for specified degrees. If gyro is used, it will adjust the speed of each motor to maintain a straight line. If not, encoders are used to maintain a straight line.
     * @param speed Speed of the motors.
     * @param degrees Distance in degrees to move.
     * @param brake Whether to brake at the end of movement (default: true).
     */
    void straight(int speed, int degrees, bool brake = true);

    /**
     * @brief spotTurn Moves the motors in a spot turn for specified degrees. If gyro is used, it will adjust the speed of each motor to maintain a straight line. If not, encoders are used to maintain a straight line.
     *
     * @param speed Speed of the motors.
     * @param degrees Angle in robot degrees to turn.
     * @param brake Whether to brake at the end of movement (default: true).
     */
    void spotTurn(int speed, int degrees, bool brake = true);

    /**
     * @brief Moves the motors in a pivot turn for specified degrees. If gyro is used, it will adjust the speed of each motor to maintain a straight line. If not, encoders are used to maintain a straight line.
     * @param speed Speed of the motor.
     * @param angle Angle in robot degrees to turn.
     * @param brake Whether to brake at the end of movement (default: true).
     */
    void pivotTurn(int speed, int degrees, bool brake = true);
};
#endif
