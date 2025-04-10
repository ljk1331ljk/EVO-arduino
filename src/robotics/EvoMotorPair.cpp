#include "EvoMotorPair.h"

EvoMotorPair::EvoMotorPair(EvoMotor *m1, EvoMotor *m2, EvoBNO055 *imu)
{
    if (imu != NULL){
        _imu = imu;
        _imuAvailable = true;
    }
    _m1 = m1;
    _m2 = m2;
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
    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < degToDecel)
    {
        if (leftSpeed == 0)
        {
            currentLeftSpeed = 0;
            currentRightSpeed = right * rightDir;
            right += _accel;
        }
        else if (rightSpeed == 0)
        {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;
            left += _accel;
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
            right -= _decel;
        }
        else if (rightSpeed == 0)
        {
            currentLeftSpeed = left * leftDir;
            currentRightSpeed = 0;
            left -= _decel;
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
                right += _accel;
            }
            else if (rightSpeed == 0)
            {
                currentLeftSpeed = left * leftDir;
                currentRightSpeed = 0;
                left += _accel;
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

bool EvoMotorPair::IMUAvailable(){
    return _IMUAvailable;
}
    
void EvoMotorPair::useIMU(bool useIMU = true){
    _useIMU = useIMU;
}

void EvoMotorPair::straightDegrees(int speed, int degrees, bool brake = true){
        
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
    

    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < degToDecel)
    {
        if (_useIMU){
            error = (int)(imu.getEulerX()* 100.0);    
        } 
        else 
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
        }
        
        PSync = error * _kpSync;
        DSync = (error - pError) * _kdSync;
        
        
        _m1->run((currentSpeed - (PSync + DSync)) * dir);
        _m2->run((currentSpeed + (PSync + DSync)) * dir);
        
        if (currentSpeed  < abs(speed))
        {
            currentSpeed += _accel;
        }
        pError = error;
    }

    while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(degrees))
    {
        if (_useIMU){
            error = (int)(imu.getEulerX()* 100.0);    
        } 
        else 
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
        }
        
        PSync = error * _kpSync;
        DSync = (error - pError) * _kdSync;
        
        _m1->run((currentSpeed - (PSync + DSync)) * dir);
        _m2->run((currentSpeed + (PSync + DSync)) * dir);
        
        if (currentSpeed  < abs(speed))
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

void EvoMotorPair::spotTurn(int speed, int degrees, bool brake = true){
    int dir;
    int degToDecel, error, pError = 0;
    int PSync, DSync;
    int currentSpeed = _minSpeed;
    if (speed !=0 && degrees != 0)
    {
        dir = ((degrees > 0) ? 1 : -1) * ((speed > 0) ? 1 : -1;
        // with positive power , positive dir is turning right, negative dir turning left
        if (_useIMU){ // requite wheel spacing and wheel size to compute accel and decel distance
            if (abs(degrees) > (_accelDeg + _decelDeg))
            {
                degToDecel = abs(degrees) - _decelDeg;
            }
            else
            {
                degToDecel = abs(degrees) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
            }
        }
        else 
        {
            if (abs(degrees) > (_accelDeg + _decelDeg))
            {
                degToDecel = abs(degrees) - _decelDeg;
            }
            else
            {
                degToDecel = abs(degrees) * _accelDeg / (_accelDeg + _decelDeg); // assuming same rate of accel and decel
            }    
        }
        
        _m1->resetAngle();
        _m2->resetAngle();
        
    
        while (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < degToDecel)
        {
            error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
            currentLeftSpeed = (speed - (PSync + DSync)) * dir;
            currentRightSpeed = (speed + (PSync + DSync)) * dir;
            
            
            _m1->run((currentSpeed - (PSync + DSync)) * dir);
            _m2->run((currentSpeed + (PSync + DSync)) * dir * -1);
            
            if (currentSpeed  < abs(speed))
            {
                currentSpeed += _accel;
            }
            pError = error;
        }
    
        while (true)
        {
            if (_useIMU){
                error = (int)(imu.getEulerX()* 100.0);    
            } 
            else 
            {
                error = abs(_m1->getAngle()) - abs(_m2->getAngle());
            }
            
            PSync = error * _kpSync;
            DSync = (error - pError) * _kdSync;
            
            
            _m1->run((currentSpeed - (PSync + DSync)) * dir);
            _m2->run((currentSpeed + (PSync + DSync)) * dir * -1);
            
            if (currentSpeed  < abs(speed))
            {
                currentSpeed -= _decel;
            }
            pError = error;
            
            if (_useIMU){
                if (abs (imu.getEulerX()) > abs(degrees)){
                    break;
                }
            }
            else {
                if (((abs(_m1->getAngle()) + abs(_m2->getAngle())) / 2) < abs(degrees)){
                    break;
                }
            }
        }
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

void EvoMotorPair::pivotTurn(int speed, int angle, bool brake = true){
    
}