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

void EvoMotorPair::setPID(float kp, float ki, float kd)
{
    _kpSync = kp;
    _kiSync = ki;
    _kdSync = kd;
}

void EvoMotorPair::move(int leftSpeed, int rightSpeed)
{
    _m1->run(leftSpeed);
    _m2->run(rightSpeed);
}

void EvoMotorPair::moveDegrees(int leftSpeed, int rightSpeed, int degrees, MotorStop stopBehaviour)
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
    int leftEnc = _m1->getAngle() / leftPowerRatio, rightEnc = _m2->getAngle() / rightPowerRatio;
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
            rSpeed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * rightEnc)), abs(maxSpeed)) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * leftEnc)), abs(maxSpeed)) * leftDir;
        }
        _m1->run(constrain(lSpeed, -4000, 4000));
        _m2->run(constrain(rSpeed, -4000, 4000));
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

            speed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (enc - (degrees - decelDist)))), abs(endSpeed));

            int sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

            lSpeed = (speed * leftPowerRatio - sync) * leftDir;
            rSpeed = (speed * rightPowerRatio + sync) * rightDir;
        }
        else if (leftSpeed == 0)
        {
            enc = rightEnc;
            lSpeed = 0;
            rSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (rightEnc - (degrees - decelDist)))), abs(endSpeed)) * rightDir;
        }
        else if (rightSpeed == 0)
        {
            enc = leftEnc;
            rSpeed = 0;
            lSpeed = max(int(sqrt(maxSpeed * maxSpeed - 2 * decel * (leftEnc - (degrees - decelDist)))), abs(endSpeed)) * leftDir;
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

void EvoMotorPair::moveDegrees(int leftSpeed, int rightSpeed, int degrees)
{
    moveDegrees(leftSpeed, rightSpeed, degrees, _stopBehavior);
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

void EvoMotorPair::spotTurnIMU(int moveSpeed, float heading, float decelHeading, MotorStop stopBehaviour)
{
    float currentHeading = _imu->getRelativeHeading();
    _m1->resetAngle();
    _m2->resetAngle();
    int leftDir = heading > 0 ? 1 : -1;
    int rightDir = heading > 0 ? -1 : 1;
    int maxSpeed = moveSpeed;
    int accel, decel, accelDist, decelDist, startSpeed, endSpeed;
    float leftPowerRatio, rightPowerRatio;

    leftPowerRatio = 1;
    rightPowerRatio = 1;

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
        endSpeed = maxSpeed;
    }
    else
    {
        endSpeed = _endSpeed;
    }

    int encPError = 0;
    int integralError[20] = {0};
    float integralIMUError[20] = {0};
    int integralIndex = 0;
    int integralSum = 0;
    int integralimuSum = 0;
    int speed = startSpeed;
    int leftEnc = _m1->getAngle() / leftPowerRatio, rightEnc = _m2->getAngle() / rightPowerRatio;
    int enc = (leftEnc * leftDir + rightEnc * rightDir) / 2;
    int encError = leftEnc * leftDir - rightEnc * rightDir;
    int lSpeed, rSpeed;
    int sync;
    int imukp = 20;
    int imukd = 1000;
    float imuerror = 0;
    int imuperror = 0;

    // ==================== ACCELERATION PHASE ====================
    while (_imu->getRelativeHeading() < currentHeading + heading - decelHeading)
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        enc = (leftEnc + rightEnc) / 2;
        encError = leftEnc - rightEnc;

        integralSum += encError - integralError[(integralIndex + 19) % 20];
        integralError[integralIndex] = encError;

        imuerror = (currentHeading + heading - _imu->getRelativeHeading());
        integralimuSum += imuerror - integralIMUError[(integralIndex + 19) % 20];
        integralIMUError[integralIndex] = imuerror;

        speed = min(int(sqrt(startSpeed * startSpeed + 2 * accel * enc)), maxSpeed);

        sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

        lSpeed = (speed * leftPowerRatio - sync) * leftDir;
        rSpeed = (speed * rightPowerRatio + sync) * rightDir;

        _m1->run(constrain(lSpeed, -4000, 4000));
        _m2->run(constrain(rSpeed, -4000, 4000));
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
    }

    maxSpeed = speed;
    double timenow = millis();

    while (abs(integralimuSum) > 1 || abs(imuerror) > 1)
    {
        leftEnc = _m1->getAngle() / leftPowerRatio * leftDir;
        rightEnc = _m2->getAngle() / rightPowerRatio * rightDir;

        enc = (leftEnc + rightEnc) / 2;
        encError = leftEnc - rightEnc;

        integralSum += encError - integralError[(integralIndex + 19) % 20];
        integralError[integralIndex] = encError;

        imuerror = (currentHeading + heading - _imu->getRelativeHeading());

        integralimuSum += imuerror - integralIMUError[(integralIndex + 19) % 20];
        integralIMUError[integralIndex] = imuerror;

        speed = (imuerror * imukp + (imuerror - imuperror) * imukd) * (maxSpeed - endSpeed) / endSpeed;
        if (speed > 0)
        {
            speed += endSpeed;
        }
        else
        {
            speed -= endSpeed;
        }

        int sync = encError * _kpSync + (encError - encPError) * _kdSync + integralSum * _kiSync;

        lSpeed = (speed * leftPowerRatio - sync) * leftDir;
        rSpeed = (speed * rightPowerRatio + sync) * rightDir;

        _m1->run(lSpeed);
        _m2->run(rSpeed);
        integralIndex = (integralIndex + 1) % 20;
        encPError = encError;
        imuperror = imuerror;
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

// void EvoMotorPair::moveIMU(int leftSpeed, int rightSpeed, int Condition, float IMUkp, float IMUkd, bool brake)
// {
//     _m1->resetAngle();
//     _m2->resetAngle();
//     int currentLeftSpeed, currentRightSpeed, degToDecel, angToDecel;
//     float leftPowerRatio, rightPowerRatio, currentHeading, error, prevError = 0, P, D;
//     int left _startSpeed;
//     int right = _startSpeed;
//     float initialHeading = _imu->getRelativeHeading();

//     int leftDir = leftSpeed == 0 ? 0 : (leftSpeed > 0 ? 1 : -1);
//     int rightDir = rightSpeed == 0 ? 0 : (rightSpeed > 0 ? 1 : -1);

//     if (leftSpeed != 0 && rightSpeed != 0)
//     {
//         leftPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? 1 : abs((float)rightSpeed / (float)leftSpeed);
//         rightPowerRatio = abs(leftSpeed) > abs(rightSpeed) ? abs((float)leftSpeed / (float)rightSpeed) : 1;
//     }
//     else
//     {
//         leftPowerRatio = leftSpeed == 0 ? 0 : 1;
//         rightPowerRatio = leftSpeed == 0 ? 1 : 0;
//     }

//     if (leftSpeed == rightSpeed && leftSpeed != 0 && rightSpeed != 0)
//     {
//         if (IMUkp == 0 && IMUkd == 0)
//         {
//             IMUkp = 10;
//             IMUkd = 50;
//         }

//         if (abs(Condition) > (_accelDeg + _decelDeg))
//         {
//             degToDecel = abs(Condition) - _decelDeg;
//         }
//         else
//         {
//             degToDecel = abs(Condition) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
//         }

//         while ((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2 < degToDecel)
//         {
//             error = initialHeading - _imu->getRelativeHeading();
//             P = error * _kpSync;
//             D = (error - prevError) * _kdSync;
//             currentLeftSpeed = (left - (P + D) * rightPowerRatio) * leftDir;
//             currentRightSpeed = (right + (P + D) * leftPowerRatio) * rightDir;
//             if (left < leftSpeed && right < rightSpeed)
//             {
//                 left += _accel;
//                 right += _accel;
//             }
//             prevError = error;

//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(Condition))
//         {
//             error = initialHeading - _imu->getRelativeHeading();
//             P = error * IMUkp;
//             D = (error - prevError) * IMUkd;
//             currentLeftSpeed = (left - (P + D) * rightPowerRatio) * leftDir;
//             currentRightSpeed = (right + (P + D) * leftPowerRatio) * rightDir;
//             if (left > _minSpeed && right > _minSpeed)
//             {
//                 left -= _decel;
//                 right -= _decel;
//             }
//             prevError = error;

//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         if (brake)
//         {
//             _m1->brake();
//             _m2->brake();
//         }
//         else
//         {
//             _m1->coast();
//             _m2->coast();
//         }
//     }

//     if (rightSpeed == 0)
//     {
//         Serial.print("RightMotor = 0");
//         while (abs(_imu->getRelativeHeading() - initialHeading) < (2 * abs(Condition)) / 3)
//         {
//             currentLeftSpeed = left * leftDir;
//             currentRightSpeed = 0;
//             if (left < abs(leftSpeed))
//             {
//                 left += _accel;
//             }
//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         while (abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))
//         {
//             currentLeftSpeed = left * leftDir;
//             currentRightSpeed = 0;
//             if (left > abs(_minSpeed))
//             {
//                 left -= _decel;
//             }
//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         if (brake)
//         {
//             _m1->brake();
//             _m2->brake();
//         }
//         else
//         {
//             _m1->coast();
//             _m2->coast();
//         }
//     }

//     if (leftSpeed == 0)
//     {
//         Serial.print("LeftMotor = 0");
//         while (abs(_imu->getRelativeHeading() - initialHeading) < (2 * abs(Condition)) / 3)
//         {
//             currentLeftSpeed = 0;
//             currentRightSpeed = right * rightDir;
//             if (right < abs(rightSpeed))
//             {
//                 right += _accel;
//             }
//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         while (abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))
//         {
//             currentLeftSpeed = 0;
//             currentRightSpeed = right * rightDir;

//             if (right > abs(_minSpeed))
//             {
//                 right -= _decel;
//             }

//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         if (brake)
//         {
//             _m1->brake();
//             _m2->brake();
//         }
//         else
//         {
//             _m1->coast();
//             _m2->coast();
//         }
//     }
//     else if (leftSpeed != rightSpeed)
//     {
//         Serial.print("Different Speed");
//         while (abs(_imu->getRelativeHeading() - initialHeading) < (2 * abs(Condition)) / 3)
//         {
//             error = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
//             P = error * _kpSync;
//             D = (error - prevError) * _kdSync;
//             currentLeftSpeed = ((left - ((P + D)) * rightPowerRatio)) * leftDir;
//             currentRightSpeed = ((right + ((P + D)) * leftPowerRatio)) * rightDir;
//             if (left < abs(leftSpeed) && right < abs(rightSpeed))
//             {
//                 left += _accel;
//                 right += _accel;
//             }
//             prevError = error;

//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         while (abs(_imu->getRelativeHeading() - initialHeading) < abs(Condition))
//         {
//             error = (_m1->getAngle() * leftPowerRatio * leftDir) - (_m2->getAngle() * rightPowerRatio * rightDir);
//             P = error * _kpSync;
//             D = (error - prevError) * _kdSync;
//             currentLeftSpeed = ((left - ((P + D)) * rightPowerRatio)) * leftDir;
//             currentRightSpeed = ((right + ((P + D)) * leftPowerRatio)) * rightDir;
//             if (left > _minSpeed && right > _minSpeed)
//             {
//                 left -= _decel;
//                 right -= _decel;
//             }
//             prevError = error;

//             _m1->run(currentLeftSpeed);
//             _m2->run(currentRightSpeed);
//         }

//         if (brake)
//         {
//             _m1->brake();
//             _m2->brake();
//         }
//         else
//         {
//             _m1->coast();
//             _m2->coast();
//         }
//     }
// }

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
