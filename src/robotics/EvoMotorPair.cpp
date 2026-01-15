#include "EvoMotorPair.h"

EvoMotorPair::EvoMotorPair(EvoMotor *m1, EvoMotor *m2, EvoIMU *imu)
{
    _m1 = m1;
    _m2 = m2;
    _imu = imu;
}
void EvoMotorPair::setStartSpeed(int startSpeed)
{
    _startSpeed = abs(startSpeed);
}
void EvoMotorPair::setEndSpeed(int endSpeed)
{
    _endSpeed = abs(endSpeed);
}

void EvoMotorPair::setAcceleration(int accel)
{
    _accel = abs(accel);
}

int EvoMotorPair::getAcceleration()
{
    return _accel;
}

void EvoMotorPair::setDeceleration(int decel)
{
    _decel = abs(decel);
}

int EvoMotorPair::getDeceleration()
{
    return _decel;
}

void EvoMotorPair::setStopBehavior(MotorStop stopBehavior)
{
    _stopBehavior = stopBehavior;
}

void EvoMotorPair::setSyncPID(int kp, int ki, int kd)
{
    _kpSync = kp;
    _kiSync = ki;
    _kdSync = kd;
}

void EvoMotorPair::setGyroPID(float kp, float ki, float kd)
{
    _kpGyro = kp;
    _kiGyro = ki;
    _kdGyro = kd;
}

void EvoMotorPair::move(int leftSpeed, int rightSpeed)
{
    _m1->run(leftSpeed);
    _m2->run(rightSpeed);
}

void EvoMotorPair::moveDegrees(int leftSpeed, int rightSpeed, int degrees, MotorStop stopBehaviour = MotorStop::HOLD)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
    int rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);
    int maxSpeed = max(leftSpeed * leftDir, rightSpeed * rightDir);
    int accel, decel, accelDist, decelDist, startSpeed, endSpeed;
    float leftPowerRatio, rightPowerRatio;
    // calculate power ratios
    if (abs(leftSpeed) == abs(rightSpeed))
    {
        leftPowerRatio = 1;
        rightPowerRatio = 1;
    }
    else if (leftSpeed != 0 && rightSpeed != 0)
    {
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)leftSpeed / (float)rightSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)rightSpeed / (float)leftSpeed) : 1;
    }
    else
    {
        leftPowerRatio = leftSpeed == 0 ? 0 : 1;
        rightPowerRatio = rightSpeed == 0 ? 0 : 1;
    }

    // calculate accel and decel distances
    if (maxSpeed < _startSpeed) // no acceleration phase
    {
        accel = 0;
        accelDist = 0;
        startSpeed = maxSpeed;
    }
    else
    {
        if (leftSpeed == 0 || rightSpeed == 0)
        {
            accel = _accel * 2;
        }
        else
        {
            accel = _accel;
        }
        startSpeed = _startSpeed;
        accelDist = (maxSpeed * maxSpeed - startSpeed * startSpeed) / 2 / accel;
    }
    if (maxSpeed < _endSpeed) // no deceleration phase
    {
        decel = 0;
        decelDist = 0;
        endSpeed = maxSpeed;
    }
    else
    {
        if (leftSpeed == 0 || rightSpeed == 0)
        {
            decel = _decel * 2;
        }
        else
        {
            decel = _decel;
        }
        endSpeed = _endSpeed;
        decelDist = (maxSpeed * maxSpeed - endSpeed * endSpeed) / 2 / decel;
    }
    // adjust peak speed if accel+decel distances exceed total distance
    if (accelDist + decelDist > degrees)
    {
        decelDist = ((startSpeed * startSpeed - endSpeed * endSpeed) / 2 + accel * degrees) / (accel + decel);
        accelDist = degrees - decelDist;
        maxSpeed = int(sqrt(startSpeed * startSpeed + 2 * accel * accelDist));
    }

    int encPError = 0;
    int integralError[20] = {0};
    int integralIndex = 0;
    int integralSum = 0;
    int speed = startSpeed;
    int leftEnc = _m1->getAngle() / leftPowerRatio;
    int rightEnc = _m2->getAngle() / rightPowerRatio;
    int enc = (leftEnc * leftDir + rightEnc * rightDir) / 2;
    int encError = leftEnc * leftDir - rightEnc * rightDir;
    int lSpeed, rSpeed;
    int sync;

    // ==================== ACCELERATION PHASE ====================
    while (enc < (degrees - decelDist))
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        if (leftSpeed != 0 && rightSpeed != 0)
        {
            enc = (leftEnc + rightEnc) / 2;
            encError = leftEnc - rightEnc;

            integralSum += encError - integralError[(integralIndex + 19) % 20];
            integralError[integralIndex] = encError;

            speed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * enc)), maxSpeed);

            sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

            lSpeed = (speed * leftPowerRatio - sync) * leftDir;
            rSpeed = (speed * rightPowerRatio + sync) * rightDir;
        }
        else if (leftSpeed == 0)
        {
            enc = rightEnc;
            lSpeed = 0;
            rSpeed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * rightEnc)), maxSpeed) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * leftEnc)), maxSpeed) * leftDir;
        }
        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
    }
    while (enc < degrees)
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        if (leftSpeed != 0 && rightSpeed != 0)
        {
            enc = (leftEnc + rightEnc) / 2;
            encError = leftEnc - rightEnc;

            integralSum += encError - integralError[(integralIndex + 19) % 20];
            integralError[integralIndex] = encError;

            speed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (enc - (degrees - decelDist)))), endSpeed);

            int sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

            lSpeed = (speed * leftPowerRatio - sync) * leftDir;
            rSpeed = (speed * rightPowerRatio + sync) * rightDir;
        }
        else if (leftSpeed == 0)
        {
            enc = rightEnc;
            lSpeed = 0;
            rSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (rightEnc - (degrees - decelDist)))), endSpeed) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (leftEnc - (degrees - decelDist)))), endSpeed) * leftDir;
        }

        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
    }

    if (stopBehaviour == MotorStop::HOLD)
    {
        _m2->hold();
        _m1->hold();
    }
    else if (stopBehaviour == MotorStop::BRAKE)
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

void EvoMotorPair::moveTime(int leftSpeed, int rightSpeed, int timems, int slowdowntime, MotorStop stopBehaviour)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
    int rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);
    int maxSpeed = max(leftSpeed * leftDir, rightSpeed * rightDir);
    float leftPowerRatio, rightPowerRatio;
    if (abs(leftSpeed) == abs(rightSpeed))
    {
        leftPowerRatio = 1;
        rightPowerRatio = 1;
    }
    else if (leftSpeed != 0 && rightSpeed != 0)
    {
        leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)leftSpeed / (float)rightSpeed);
        rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)rightSpeed / (float)leftSpeed) : 1;
    }
    else
    {
        leftPowerRatio = leftSpeed == 0 ? 0 : 1;
        rightPowerRatio = rightSpeed == 0 ? 0 : 1;
    }
    int accel = _accel, decel = _decel;
    if (leftSpeed == 0 || rightSpeed == 0)
    {
        accel = _accel * 2;
        decel = _decel * 2;
    }

    long timenow = millis();

    int encPError = 0;
    int integralError[20] = {0};
    int integralIndex = 1;
    int integralSum = 0;
    int speed = _startSpeed;
    int leftEnc = _m1->getAngle() / leftPowerRatio, rightEnc = _m2->getAngle() / rightPowerRatio;
    int enc = (leftEnc * leftDir + rightEnc * rightDir) / 2;
    int encError = leftEnc * leftDir - rightEnc * rightDir;
    int lSpeed, rSpeed;
    while (timenow + timems - slowdowntime > millis())
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        if (leftSpeed != 0 && rightSpeed != 0)
        {
            enc = (leftEnc + rightEnc) / 2;
            encError = leftEnc - rightEnc;

            integralError[integralIndex] = encError;
            integralSum += encError - integralError[(integralIndex - 1) % 20];

            speed = min(int(sqrt(_startSpeed * _startSpeed + 2 * accel * enc)), abs(maxSpeed));

            int sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

            lSpeed = (speed * leftPowerRatio - sync) * leftDir;
            rSpeed = (speed * rightPowerRatio + sync) * rightDir;
        }
        else if (leftSpeed == 0)
        {
            enc = rightEnc;
            lSpeed = 0;
            rSpeed = min(int(sqrt(_startSpeed * _startSpeed + 2 * accel * rightEnc)), abs(maxSpeed)) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = min(int(sqrt(_startSpeed * _startSpeed + 2 * accel * leftEnc)), abs(maxSpeed)) * leftDir;
        }
        _m1->run(constrain(lSpeed, -4000, 4000));
        _m2->run(constrain(rSpeed, -4000, 4000));
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
    }
    while (timenow + timems > millis())
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        if (leftSpeed != 0 && rightSpeed != 0)
        {
            enc = (leftEnc + rightEnc) / 2;
            encError = leftEnc - rightEnc;

            integralError[integralIndex] = encError;
            integralSum += encError - integralError[(integralIndex - 1) % 20];

            speed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * enc)), abs(_endSpeed));

            int sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

            lSpeed = (speed * leftPowerRatio - sync) * leftDir;
            rSpeed = (speed * rightPowerRatio + sync) * rightDir;
        }
        else if (leftSpeed == 0)
        {
            enc = rightEnc;
            lSpeed = 0;
            rSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * rightEnc)), abs(_endSpeed)) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * leftEnc)), abs(_endSpeed)) * leftDir;
        }
        _m1->run(constrain(lSpeed, -4000, 4000));
        _m2->run(constrain(rSpeed, -4000, 4000));
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
    }
    if (stopBehaviour == MotorStop::HOLD)
    {
        _m1->hold();
        _m2->hold();
    }
    else if (stopBehaviour == MotorStop::BRAKE)
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

void EvoMotorPair::spotTurnGyro(int motorSpeed, float heading, bool reset, MotorStop stopBehaviour)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int dir = motorSpeed == 0 ? 0 : (motorSpeed > 0 ? 1 : -1);
    int maxSpeed = abs(motorSpeed);
    int accel, decel, accelHeading, decelHeading, startSpeed, endSpeed;
    if (reset)
    {
        _imu->resetHeading();
    }
    float currentHeading = _imu->getRelativeHeading();
    float headingError = heading - currentHeading;

    float headingPError = 0;
    int integralPError = 0;
    int integralError[20] = {0};
    float gyroIntegralError[20] = {0};
    int integralIndex = 0;
    int integralSum = 0;
    float gyroIntegralSum = 0;
    int speed = startSpeed;
    int leftEnc = _m1->getAngle();
    int rightEnc = _m2->getAngle();
    int encError = leftEnc - rightEnc;
    int encPError = 0;
    int lSpeed, rSpeed;
    int sync;
    unsigned long timenow = millis();
    if (heading == -1)
    {
        _imu->resetHeading();
        heading = 0;
    }
    // ==================== ACCELERATION PHASE ====================
    while ((abs(headingError) > 2))
    {

        currentHeading = _imu->getRelativeHeading();
        headingError = heading - currentHeading;

        gyroIntegralSum += headingError - gyroIntegralError[(integralIndex + 19) % 20];
        gyroIntegralError[integralIndex] = headingError;

        speed = (int)(headingError * _kpGyro + (headingError - headingPError) * _kdGyro + gyroIntegralSum * _kiGyro);
        int speedDir = speed == 0 ? 0 : (speed > 0 ? 1 : -1);
        speed = min(abs(speed), maxSpeed) * speedDir;

        leftEnc = _m1->getAngle();
        rightEnc = _m2->getAngle();
        encError = leftEnc - rightEnc;
        integralSum += encError - integralError[(integralIndex + 19) % 20];
        sync = (encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync) * dir;
        lSpeed = (speed - sync);
        rSpeed = (speed + sync) * -1;

        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        headingPError = headingError;
        encPError = encError;
    }

    if (stopBehaviour == MotorStop::HOLD)
    {
        _m2->hold();
        _m1->hold();
    }
    else if (stopBehaviour == MotorStop::BRAKE)
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

void EvoMotorPair::StraightDegreesIMU(int motorSpeed, int degrees, int heading, MotorStop stopBehaviour)
{
    _m1->resetAngle();
    _m2->resetAngle();
    int dir = motorSpeed == 0 ? 0 : (motorSpeed > 0 ? 1 : -1);
    int maxSpeed = abs(motorSpeed);
    int accel, decel, accelDist, decelDist, startSpeed, endSpeed;

    // calculate accel and decel distances
    if (maxSpeed < _startSpeed) // no acceleration phase
    {
        accel = 0;
        accelDist = 0;
        startSpeed = maxSpeed;
    }
    else
    {
        accel = _accel;
        startSpeed = _startSpeed;
        accelDist = (maxSpeed * maxSpeed - startSpeed * startSpeed) / 2 / accel;
    }
    if (maxSpeed < _endSpeed) // no deceleration phase
    {
        decel = 0;
        decelDist = 0;
        endSpeed = maxSpeed;
    }
    else
    {
        decel = _decel;
        endSpeed = _endSpeed;
        decelDist = (maxSpeed * maxSpeed - endSpeed * endSpeed) / 2 / decel;
    }
    // adjust peak speed if accel+decel distances exceed total distance
    if (accelDist + decelDist > degrees)
    {
        decelDist = ((startSpeed * startSpeed - endSpeed * endSpeed) / 2 + accel * degrees) / (accel + decel);
        accelDist = degrees - decelDist;
        maxSpeed = int(sqrt(startSpeed * startSpeed + 2 * accel * accelDist));
    }

    float headingPError = 0;
    float integralError[20] = {0};
    int integralIndex = 0;
    float integralSum = 0;
    int speed = startSpeed;
    int leftEnc = _m1->getAngle();
    int rightEnc = _m2->getAngle();
    int enc = (leftEnc + rightEnc) * dir / 2;
    int lSpeed, rSpeed;
    int sync;
    if (heading == -1)
    {
        _imu->resetHeading();
        heading = 0;
    }
    float headingError = _imu->getRelativeHeading() - heading;

    // ==================== ACCELERATION PHASE ====================
    while (enc < (degrees - decelDist))
    {
        leftEnc = _m1->getAngle();
        rightEnc = _m2->getAngle();

        enc = (leftEnc + rightEnc) * dir / 2;
        headingError = _imu->getRelativeHeading() - heading;

        integralSum += headingError - integralError[(integralIndex + 19) % 20];
        integralError[integralIndex] = headingError;

        speed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * enc)), maxSpeed);

        sync = (headingError * _kpGyro + (headingError - headingPError) * _kdGyro + integralSum * _kiGyro) * dir;

        lSpeed = (speed - sync) * dir;
        rSpeed = (speed + sync) * dir;

        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        headingPError = headingError;
    }
    while (enc < degrees)
    {
        leftEnc = _m1->getAngle();
        rightEnc = _m2->getAngle();

        enc = (leftEnc + rightEnc) * dir / 2;
        headingError = _imu->getRelativeHeading() - heading;

        integralSum += headingError - integralError[(integralIndex + 19) % 20];
        integralError[integralIndex] = headingError;

        speed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (enc - (degrees - decelDist)))), endSpeed);

        sync = (headingError * _kpGyro + (headingError - headingPError) * _kdGyro + integralSum * _kiGyro) * dir;

        lSpeed = (speed - sync) * dir;
        rSpeed = (speed + sync) * dir;

        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        headingPError = headingError;
    }

    if (stopBehaviour == MotorStop::HOLD)
    {
        _m2->hold();
        _m1->hold();
    }
    else if (stopBehaviour == MotorStop::BRAKE)
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

void EvoMotorPair::hold()
{
    _m1->hold();
    _m2->hold();
}

void EvoMotorPair::resetAngle()
{
    _m1->resetAngle();
    _m2->resetAngle();
}
