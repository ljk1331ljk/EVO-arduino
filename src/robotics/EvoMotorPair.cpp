#include "EvoMotorPair.h"


EvoMotorPair::EvoMotorPair(EvoMotor *m1, EvoMotor *m2, int wheelDiameter, int axleTrack, EvoBNO055 *imu)
{
    if (imu != NULL)
    {
        _imu = imu;
        _imuAvailable = true;
    }
    _m1 = m1;
    _m2 = m2;
    _wheelDiameter = wheelDiameter;
    _axleTrack = axleTrack;
    _gyroEncoderFactor = _axleTrack / _wheelDiameter;
}

void EvoMotorPair::setMinimumSpeed(int minSpeed)
{
    _minSpeed = minSpeed;
}

void EvoMotorPair::setWheelDiameter(int wheelDiameter, int axleTrack)
{
    _wheelDiameter = wheelDiameter;
    _axleTrack = axleTrack;
    _gyroEncoderFactor = _axleTrack / _wheelDiameter;
}

void EvoMotorPair::getWheelDiameter(int *wheelDiameter, int *axleTrack)
{
    *wheelDiameter = _wheelDiameter;
    *axleTrack = _axleTrack;
}

void EvoMotorPair::setAcceleration(float accel, int accelDeg)
{
    _accel = accel;
    _accelDeg = accelDeg;
}

void EvoMotorPair::setDeceleration(float decel, int decelDeg)
{
    _decel = decel;
    _decelDeg = decelDeg;
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
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs(rightSpeed / leftSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs(leftSpeed / rightSpeed) : 1;
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
    float leftEncoderRatio = leftSpeed / (leftSpeed + rightSpeed);
    float rightEncoderRatio = rightSpeed / (leftSpeed + rightSpeed);

    while (((abs(_m1->getAngle()) * leftEncoderRatio + abs(_m2->getAngle())) * rightEncoderRatio) < degToDecel)
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
            degError = abs(_m1->getAngle() * leftPowerRatio) - abs(_m2->getAngle() * rightPowerRatio);
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
            degError = abs(_m1->getAngle() * leftPowerRatio) - abs(_m2->getAngle() * rightPowerRatio);
            PSync = degError * _kpSync;
            DSync = (degError - pDegError) * _kdSync;
            currentLeftSpeed = ((left - ((PSync + DSync)) * rightPowerRatio)) * leftDir;
            currentRightSpeed = ((right + ((PSync + DSync)) * leftPowerRatio)) * rightDir;
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
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs(rightSpeed / leftSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs(leftSpeed / rightSpeed) : 1;
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
        degError = abs(_m1->getAngle() * leftPowerRatio) - abs(_m2->getAngle() * rightPowerRatio);
        PSync = degError * _kpSync;
        DSync = (degError - pDegError) * _kdSync;
        currentLeftSpeed = ((left - ((PSync + DSync)) * rightPowerRatio)) * leftDir;
        currentRightSpeed = ((right + ((PSync + DSync)) * leftPowerRatio)) * rightDir;
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

int EvoMotorPair::getAngle()
{
    return (_m1->getAngle() + _m2->getAngle());
}

bool EvoMotorPair::imuAvailable()
{
    return _imuAvailable;
}

void EvoMotorPair::useIMU(bool useImu)
{
    _useImu = useImu;
}

void EvoMotorPair::straight(int speed, int degrees, bool brake)
{

    int dir;
    int degToDecel, error, pError = 0;
    int PSync, DSync;
    int currentSpeed = _minSpeed;
    dir = (speed == 0) ? 0 : (speed > 0 ? 1 : -1);

    if (abs(degrees) > (_accelDeg + _decelDeg))
    {
        degToDecel = abs(degrees) - _decelDeg;
    }
    else
    {
        degToDecel = abs(degrees) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
    }

    _m1->resetAngle();
    _m2->resetAngle();
    _imu->resetHeading();
    float _kpgyrosync = 1.0;
    float _kdgyrosync = 30.0;

    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < degToDecel)
    {
        if (_useImu)
        {
            error = (int)(_imu->getRelativeHeading() * 100.0) * dir;
            PSync = error * _kpgyrosync;
            DSync = (error - pError) * _kdgyrosync;
        }
        else
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
        }

        _m1->run((currentSpeed - (PSync + DSync)) * dir);
        _m2->run((currentSpeed + (PSync + DSync)) * dir);

        if (currentSpeed < abs(speed))
        {
            currentSpeed += _accel;
        }
        pError = error;
    }

    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(degrees))
    {
        if (_useImu)
        {
            error = (int)(_imu->getRelativeHeading() * 100.0) * dir;
            PSync = error * _kpgyrosync;
            DSync = (error - pError) * _kdgyrosync;
        }
        else
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
        }

        _m1->run((currentSpeed - (PSync + DSync)) * dir);
        _m2->run((currentSpeed + (PSync + DSync)) * dir);

        if (currentSpeed < abs(speed))
        {
            currentSpeed -= _decel;
        }
        pError = error;
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

void EvoMotorPair::spotTurn(int speed, int degrees, bool brake)
{
    int dir;
    int degToDecel, error, pError = 0;
    int PSync, DSync;
    int currentSpeed = _minSpeed;

    if (speed != 0 && degrees != 0)
    {
        dir = ((degrees > 0) ? 1 : -1) * ((speed > 0) ? 1 : -1);
        // with positive power , positive dir is turning right, negative dir turning left
        if (_useImu)
        {
            degToDecel = abs(degrees) / 2;
            if ((float(abs(degrees)) * _gyroEncoderFactor) > (_accelDeg + _decelDeg))
            {
                degToDecel = (float(abs(degrees)) * _gyroEncoderFactor) - _decelDeg;
            }
            else
            {
                degToDecel = (float(abs(degrees)) * _gyroEncoderFactor) * _accelDeg / (_accelDeg + _decelDeg);
            }
        }
        else
        {
            if ((float(abs(degrees)) * _gyroEncoderFactor) > (_accelDeg + _decelDeg))
            {
                degToDecel = (float(abs(degrees)) * _gyroEncoderFactor) - _decelDeg;
            }
            else
            {
                degToDecel = (float(abs(degrees)) * _gyroEncoderFactor) * _accelDeg / (_accelDeg + _decelDeg);
            }
        }

        _m1->resetAngle();
        _m2->resetAngle();
        _imu->resetHeading();
        Serial.println(_imu->getRelativeHeading());

        while ((abs(_imu->getRelativeHeading()) * _gyroEncoderFactor) < degToDecel)
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());

            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;

            _m1->run(constrain((currentSpeed - (PSync + DSync)), _minSpeed, abs(speed)) * dir);
            _m2->run(constrain((currentSpeed + (PSync + DSync)), _minSpeed, abs(speed)) * dir * -1);

            if (currentSpeed < abs(speed))
            {
                currentSpeed += _accel;
            }
            pError = error;
            Serial.println(_imu->getRelativeHeading());
        }
        int kpgyro = 150;
        int kdgyro = 1500;
        int gyroPError = 0;
        int gyroError = abs(degrees) - abs(_imu->getRelativeHeading());
        while (gyroError < 0)
        {
            gyroError = abs(degrees) - abs(_imu->getRelativeHeading());
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
            int PGyro = (gyroError * kpgyro);
            int DGyro = (gyroError - gyroPError) * kdgyro;

            _m1->run(constrain((PGyro + DGyro) - (PSync + DSync), _minSpeed, abs(speed)) * dir);
            _m2->run(constrain((PGyro + DGyro) + (PSync + DSync), _minSpeed, abs(speed)) * dir * -1);

            if (currentSpeed > abs(_minSpeed))
            {
                currentSpeed -= _decel;
            }
            gyroPError = gyroError;
            pError = error;
        }
        long timenow = millis();
        while (millis() - timenow < 500)
        {
            gyroError = abs(degrees) - abs(_imu->getRelativeHeading());
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
            int PGyro = (gyroError * kpgyro);
            int DGyro = (gyroError - gyroPError) * kdgyro;

            _m1->run(constrain((PGyro + DGyro) - (PSync + DSync), _minSpeed, abs(speed)) * dir);
            _m2->run(constrain((PGyro + DGyro) + (PSync + DSync), _minSpeed, abs(speed)) * dir * -1);

            if (currentSpeed > abs(_minSpeed))
            {
                currentSpeed -= _decel;
            }
            gyroPError = gyroError;
            pError = error;
        }

        Serial0.print(currentSpeed);
        Serial0.print(" ");
        Serial0.println(_imu->getRelativeHeading());
    }
    Serial0.println(_imu->getRelativeHeading());
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

void EvoMotorPair::pivotTurn(int speed, int angle, bool brake)
{
}
