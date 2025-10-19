#include "EvoMotorPair.h"

EvoMotorPair::EvoMotorPair(EvoMotor *m1, EvoMotor *m2, EvoBNO055 *imu)
{
    _m1 = m1;
    _m2 = m2;
    _imu = imu;
}

void EvoMotorPair::setMinimumSpeed(int minSpeed)
{
    _minSpeed = minSpeed;
}

void EvoMotorPair::setAcceleration(float accel, int accelDeg)
{
    _accel = accel;
    _accelDeg = accelDeg;
}

void EvoMotorPair::getAcceleration(float &accel, int &accelDeg)
{
    accel = _accel;
    accelDeg = _accelDeg;
}

void EvoMotorPair::setDeceleration(float decel, int decelDeg)
{
    _decel = decel;
    _decelDeg = decelDeg;
}

void EvoMotorPair::getDeceleration(float &decel, int &decelDeg)
{
    decel = _decel;
    decelDeg = _decelDeg;
}

void EvoMotorPair::setPD(float kp, float kd)
{
    _kpSync = kp;
    _kdSync = kd;
}

void EvoMotorPair::move(int leftSpeed, int rightSpeed)
{
    _m1->run(leftSpeed);
    _m2->run(rightSpeed);
}

void EvoMotorPair::moveDegrees(int leftSpeed, int rightSpeed, int degrees, bool brake)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int leftDir, rightDir;
    float leftPowerRatio, rightPowerRatio;
    int left = _minSpeed;
    int right = _minSpeed;
    int degToDecel, degError, pDegError = 0;
    int PSync, DSync;

    leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
    rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);
    if (leftSpeed != 0 && rightSpeed != 0)
    {
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)rightSpeed / (float)leftSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)leftSpeed / (float)rightSpeed) : 1;
    }
    else
    {
        leftPowerRatio = leftSpeed == 0 ? 0 : 1;
        rightPowerRatio = leftSpeed == 0 ? 1 : 0;
    }

    if (abs(degrees) > (_accelDeg + _decelDeg))
    {
        degToDecel = abs(degrees) - _decelDeg;
    }
    else
    {
        degToDecel = abs(degrees) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
    }
    int currentLeftSpeed, currentRightSpeed;

    while ((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2 < degToDecel)
    {
        if (leftSpeed == 0)
        {
            currentLeftSpeed = 0;
            currentRightSpeed = right * rightDir;
            if (right < abs(rightSpeed))
            {
                right += _accel;
            }
        }
        else if (rightSpeed == 0)
        {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;
            if (left < abs(leftSpeed))
            {
                left += _accel;
            }
        }
        else
        {
            degError = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
            PSync = degError * _kpSync;
            DSync = (degError - pDegError) * _kdSync;
            currentLeftSpeed = ((left - ((PSync + DSync)) * rightPowerRatio)) * leftDir;
            currentRightSpeed = ((right + ((PSync + DSync)) * leftPowerRatio)) * rightDir;
            if (left < abs(leftSpeed) && right < abs(rightSpeed))
            {
                left += _accel;
                right += _accel;
            }
            pDegError = degError;
        }
        _m1->run(currentLeftSpeed);
        _m2->run(currentRightSpeed);
    }

    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(degrees))
    {
        if (leftSpeed == 0)
        {
            currentLeftSpeed = 0;
            currentRightSpeed = right * rightDir;

            if (right > abs(_minSpeed))
            {
                right -= _decel;
            }
        }
        else if (rightSpeed == 0)
        {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;

            if (left > abs(_minSpeed))
            {
                left -= _decel;
            }
        }
        else
        {
            degError = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
            PSync = degError * _kpSync;
            DSync = (degError - pDegError) * _kdSync;
            currentLeftSpeed = (left - (PSync + DSync) * rightPowerRatio) * leftDir;
            currentRightSpeed = (right + (PSync + DSync) * leftPowerRatio) * rightDir;
            if (left > _minSpeed && right > _minSpeed)
            {
                left -= _decel;
                right -= _decel;
            }
            pDegError = degError;
        }

        _m1->run(currentLeftSpeed);
        _m2->run(currentRightSpeed);
    }

    if (brake)
    {
        _m1->brake();
        _m2->brake();
    }
    else
    {
        _m1->coast();
        _m2->coast();
    }
}

void EvoMotorPair::moveTime(int leftSpeed, int rightSpeed, int timems, bool brake)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int leftDir, rightDir;
    float leftPowerRatio, rightPowerRatio;
    int left = _minSpeed;
    int right = _minSpeed;
    int degToDecel, degError, pDegError = 0;
    int PSync, DSync;

    leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
    rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);
    if (leftSpeed != 0 && rightSpeed != 0)
    {
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)rightSpeed / (float)leftSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)leftSpeed / (float)rightSpeed) : 1;
    }
    else
    {
        leftPowerRatio = leftSpeed == 0 ? 0 : 1;
        rightPowerRatio = leftSpeed == 0 ? 1 : 0;
    }

    int currentLeftSpeed, currentRightSpeed;
    unsigned long timenow = millis();
    while ((millis() - timenow) < timems)
    {
        if (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < _accelDeg)
        {
            if (leftSpeed == 0)
            {
                currentLeftSpeed = 0;
                currentRightSpeed = right * rightDir;
                if (right < abs(rightSpeed))
                {
                    right += _accel;
                }
            }
            else if (rightSpeed == 0)
            {
                currentLeftSpeed = left * leftDir;
                currentRightSpeed = 0;
                if (left < abs(leftSpeed))
                {
                    left += _accel;
                }
            }
            else
            {
                if (left < abs(leftSpeed) && right < abs(rightSpeed))
                {
                    left += _accel;
                    right += _accel;
                }
                pDegError = degError;
            }
        }
        degError = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
        PSync = degError * _kpSync;
        DSync = (degError - pDegError) * _kdSync;
        currentLeftSpeed = (left - (PSync + DSync) * rightPowerRatio) * leftDir;
        currentRightSpeed = (right + (PSync + DSync) * leftPowerRatio) * rightDir;
        _m1->run(currentLeftSpeed);
        _m2->run(currentRightSpeed);
    }
    if (brake)
    {
        _m1->brake();
        _m2->brake();
    }
    else
    {
        _m1->coast();
        _m2->coast();
    }
}

void EvoMotorPair::moveIMU(int leftSpeed, int rightSpeed, int Condition, float IMUkp, float IMUkd, bool brake)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int currentLeftSpeed, currentRightSpeed, degToDecel, angToDecel;
    float leftPowerRatio, rightPowerRatio, currentHeading, error, prevError = 0, P, D;
    int left = _minSpeed;
    int right = _minSpeed;
    float initialHeading = _imu->getRelativeHeading();

    int leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
    int rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);

    if (leftSpeed != 0 && rightSpeed != 0)
    {
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)rightSpeed / (float)leftSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)leftSpeed / (float)rightSpeed) : 1;
    }
    else
    {
        leftPowerRatio = leftSpeed == 0 ? 0 : 1;
        rightPowerRatio = leftSpeed == 0 ? 1 : 0;
    }

    if (leftSpeed == rightSpeed && leftSpeed != 0 && rightSpeed != 0) 
    {
        if (IMUkp == 0 && IMUkd == 0) {
            IMUkp = 10;
            IMUkd = 50;
        }

        if (abs(Condition) > (_accelDeg + _decelDeg))
        {
            degToDecel = abs(Condition) - _decelDeg;
        }
         else
        {
            degToDecel = abs(Condition) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
        }

        while ((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2 < degToDecel)
        {
            error = initialHeading - _imu->getRelativeHeading();
            P = error * _kpSync;
            D = (error - prevError) * _kdSync;
            currentLeftSpeed = (left - (P + D) * rightPowerRatio) * leftDir;
            currentRightSpeed = (right + (P + D) * leftPowerRatio) * rightDir;
            if (left < leftSpeed && right < rightSpeed)
            {
                left += _accel;
                right += _accel;
            }
            prevError = error;

            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(Condition))
        {
            error = initialHeading - _imu->getRelativeHeading();
            P = error * IMUkp;
            D = (error - prevError) * IMUkd;
            currentLeftSpeed = (left - (P + D) * rightPowerRatio) * leftDir;
            currentRightSpeed = (right + (P + D) * leftPowerRatio) * rightDir;
            if (left > _minSpeed && right > _minSpeed)
            {
                left -= _decel;
                right -= _decel;
            }
            prevError = error;

            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        if (brake)
        {
            _m1->brake();
            _m2->brake();
        }
        else
        {
            _m1->coast();
            _m2->coast();
        }
    }

    if (rightSpeed == 0)   {
        Serial.print("RightMotor = 0");
        while(abs(_imu->getRelativeHeading() - initialHeading) < (2*abs(Condition))/3)  {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;
            if (left < abs(leftSpeed))
            {
                left += _accel;  
            }
            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        while(abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))  {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;
                if (left > abs(_minSpeed))
                {
                    left -= _decel;
                }
            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        if (brake)
        {
            _m1->brake();
            _m2->brake();
        }
        else
        {
            _m1->coast();
            _m2->coast();
        }
    }

    if (leftSpeed == 0)  {
        Serial.print("LeftMotor = 0");
        while(abs(_imu->getRelativeHeading() - initialHeading) < (2*abs(Condition))/3)   {
            currentLeftSpeed = 0;
            currentRightSpeed = right * rightDir;
            if (right < abs(rightSpeed))
            {
                right += _accel;
            }
            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        while(abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))  {
            currentLeftSpeed = 0;
            currentRightSpeed = right * rightDir;

            if (right > abs(_minSpeed))
            {
                right -= _decel;
            }

            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        if (brake)
        {
            _m1->brake();
            _m2->brake();
        }
        else    
        {
            _m1->coast();
            _m2->coast();
        }
    }
    else if (leftSpeed != rightSpeed) {
        Serial.print("Different Speed");
        while (abs(_imu->getRelativeHeading() - initialHeading) < (2*abs(Condition))/3)   {
            error = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
            P = error * _kpSync;
            D = (error - prevError) * _kdSync;
            currentLeftSpeed = ((left - ((P + D)) * rightPowerRatio)) * leftDir;
            currentRightSpeed = ((right + ((P + D)) * leftPowerRatio)) * rightDir;
            if (left < abs(leftSpeed) && right < abs(rightSpeed))
            {
                left += _accel;
                right += _accel;
            }
            prevError = error;

            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        while (abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))    {
            error = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
            P = error * _kpSync;
            D = (error - prevError) * _kdSync;
            currentLeftSpeed = ((left - ((P + D)) * rightPowerRatio)) * leftDir;
            currentRightSpeed = ((right + ((P + D)) * leftPowerRatio)) * rightDir;
            if (left > _minSpeed && right > _minSpeed)
            {
                left -= _decel;
                right -= _decel;
            }
            prevError = error;

            _m1->run(currentLeftSpeed);
            _m2->run(currentRightSpeed);
        }

        if (brake)
        {
            _m1->brake();
            _m2->brake();
        }
        else
        {
            _m1->coast();
            _m2->coast();
        }
    }
}

void EvoMotorPair::brake()
{
    _m1->brake();
    _m2->brake();
}

void EvoMotorPair::coast()
{
    _m1->coast();
    _m2->coast();
}

void EvoMotorPair::resetAngle()
{
    _m1->resetAngle();
    _m2->resetAngle();
}
