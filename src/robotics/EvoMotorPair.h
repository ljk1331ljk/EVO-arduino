#ifndef EVO_MOTORPAIR_H
#define EVO_MOTORPAIR_H

#include "../motors/EvoMotor.h"

class EvoMotorPair
{
private:
    EvoMotor *_m1;
    EvoMotor *_m2;
    int _minSpeed = 800, _accelDeg = 2000, _decelDeg = 2000;
    float _accel = 8, _decel = 8, _kpSync = 20, _kdSync = 200;

public:
    // Constructor with port and positive direction
    EvoMotorPair(EvoMotor *m1, EvoMotor *m2);

    void setMinimumSpeed(int minSpeed);
    void setAcceleration(float accel, int accelDeg);
    void setDeceleration(float decel, int decelDeg);
    void setPD(float kp, float kd);

    void move(int leftSpeed, int rightSpeed);
    void moveDegrees(int leftSpeed, int rightSpeed, int degrees, bool brake = true);
    void moveTime(int leftSpeed, int rightSpeed, int timems, bool brake = true);
    void brake();
    void coast();

    void resetAngle();
    int getAngle();
};
#endif