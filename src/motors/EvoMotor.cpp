#include "EvoMotor.h"

int clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

EvoMotor::EvoMotor(MotorType motorType, MotorPort motorPort, bool motorFlip)
{
    switch (motorType)
    {
    case EV3:
        _min= -4000;
        _max = 4000;
        _countPerRevolution = 720;
        _kp = 5;
        _kd = 30;
        break;
    case ITER:
        _min = -5000;
        _max = 5000;
        _countPerRevolution = 1204;
        _kp = 10;
        _kd = 50;
        break;
    case Default:
        _min = -4000;
        _max = 4000;
        _countPerRevolution = 360;
        _kp = 5;
        _kd = 30;
        break;
    }
    
    _motorPort = motorPort;
    _motorFlip = motorFlip;
    switch (_motorPort)
    {
    case M1:
        if (!_motorFlip)
            _motorPins = {MOTOR11, MOTOR12, TACH11, TACH12};
        else
            _motorPins = {MOTOR12, MOTOR11, TACH12, TACH11};
        break;
    case M2:
        if (!_motorFlip)
            _motorPins = {MOTOR22, MOTOR21, TACH21, TACH22};
        else
            _motorPins = {MOTOR21, MOTOR22, TACH22, TACH21};
        break;
    case M3:
        if (!_motorFlip)
            _motorPins = {MOTOR31, MOTOR32, TACH31, TACH32};
        else
            _motorPins = {MOTOR32, MOTOR31, TACH32, TACH31};
        break;
    case M4:
        if (!_motorFlip)
            _motorPins = {MOTOR41, MOTOR42, TACH41, TACH42};
        else
            _motorPins = {MOTOR42, MOTOR41, TACH42, TACH41};
        break;
    }
}
void EvoMotor::begin()
{
    
    driver.begin();
    driver.setPWM(_motorPins.power1, 0, 4096);
    driver.setPWM(_motorPins.power2, 0, 4096);
    encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
    encoder.clearCount();
    xTaskCreate(motorControlTask, "Motor Control Task", 2048, this, 1, NULL);
}

void EvoMotor::setSpeedLimit(int minSpeed, int maxSpeed)
{
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
}

void EvoMotor::getSpeedLimit(int* minSpeed, int* maxSpeed)
{
    *minSpeed = _minSpeed;
    *maxSpeed = _maxSpeed;
}

void EvoMotor::setEncoderAvailable(bool encoderAvailable)
{
    _encoderAvailable = encoderAvailable;    
}
    
//Method to get encoder availability
bool EvoMotor::isEncoderAvailable()
{
    return _encoderAvailable;
}
// Method to set encoder count per revolution
void EvoMotor::setCountPerRevolution(int countPerRevolution)
{
    _countPerRevolution = countPerRevolution;
}

//Method to get encoder count per revolution
int EvoMotor::getCountPerRevolution()
{ 
    return _countPerRevolution;    
}

// Method to get the encoder count
int EvoMotor::getCount()
{
    return encoder.getConut();
}

// Method to set the encoder count
void EvoMotor::setCount(int count)
{
    encoder.setCount(count);    
}

// Method to reset the encoder count
void EvoMotor::resetCount()
{
    encoder.setCount(0);
}

// Method to get current angle
int EvoMotor::getAngle()
{
    return encoder.getCount() * 360 / _countPerRevolution;
}

// Method to reset angle
void EvoMotor::resetAngle()
{
    encoder.setCount(0);
}

void EvoMotor::setAngle(int angle)
{
    encoder.setCount(angle*_countPerRevolution/360);
}

// Method returns if the motor is stalled
bool EvoMotor::stalled(){
    return _stalled;
}


// Method to set the motor stall thersholds
void EvoMotor::setStallThresholds(int timems, int count)
{
    _stallTime = timems;
    _stallcountThreshold = count;
}

// Method to stop the motor
void EvoMotor::setStopBehaviour(MotorState motorStopState)
{
    _motorStopState = motorStopState;    
}


// Method to stop the motor using motorStopState
void EvoMotor::stop();
    switch(_motorStopState)
    {
        case BRAKE:
            brake();
            break;
        case COAST:
            coast();
            break;
        case HOLD:
            hold();
            break;
        default:
            brake();
    }
// Method to stop the motor
void EvoMotor::coast()
{
    this->_motorState = COAST;
}

// Method to brake the motor
void EvoMotor::brake()
{
    this->resetAngle();
    this->_targetAngle = 0;
    this->_motorState = BRAKE;
}

void EvoMotor::move(int speed)
{
    speed = clamp(speed, -4000, 4000);
    if (speed > 0)
    {
        driver.setPWM(_motorPins.power1, 0, speed);
        driver.setPWM(_motorPins.power2, 0, 0);
    }
    else if (speed < 0)
    {
        driver.setPWM(_motorPins.power1, 0, 0);
        driver.setPWM(_motorPins.power2, 0, -speed);
    }
    else
    {
        driver.setPWM(_motorPins.power1, 0, 4096);
        driver.setPWM(_motorPins.power2, 0, 4096);
    }
}

void EvoMotor::run(int speed)
{
    this->_motorState = RUN;
    this->move(speed);
    vTaskDelay(1 / portTICK_PERIOD_MS);
}


// Method to run the motor for a specified number of degrees
void EvoMotor::runAngle(int speed, int angle)
{
    this->resetAngle();
    this->_motorState = RUN;
    while (abs(this->getAngle()) < degrees);
    this->stop();
}

void EvoMotor::runTarget(int speed, int angle, bool blocking)
{
    this->_targetSpeed = speed;
    this->_targetAngle = angle;
    this->_completed = false;
    this->_motorState = TARGET;
    if (blocking)
    {
        while ((abs(this->getAngle()) - degrees) < 2)
            ;
    }
}

void EvoMotor::runUntilStalled(int speed)
{
    this->run(speed);
    while(!this->_stalled);
    this->stop();
}

void EvoMotor::motorControlTask(void *parameter)
{
    EvoMotor *motor = (EvoMotor *)parameter;
    int _motorSpeed;
    int _error;
    int encoder, prevencoder, lastreadtime = 0;
    int _measuredSpeed;
    for (;;)
    {
        encoder = motor->getAngle();
        switch (motor->_motorState)
        {
        case BRAKE:
            motor->move((encoder - motor->_targetAngle) * -30);
            break;
        case TARGET:
            _error = encoder - motor->_targetAngle;
            _motorSpeed = clamp(error * motor->_kp * -1, motor->_targetSpeed * -1, motor->_targetSpeed);
            motor->move(_motorSpeed);
            break;
        case COAST:
            motor->move(0);
            break;
        case RUN:
            timenow = millis();
            if ((timenow - lastreadtime)>motor->_stallTime)
            {
                if ((encoder - prevencoder) > motor->_stallcountThreshold)
                {
                    motor->_stalled = true;
                } else {
                    motor->_stalled = false;
                }
            }
            break;
        }
        vTaskDelay(1);
    }
}

void EvoMotor::setPID(float kp, float ki, float kd)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
}

void EvoMotor::getPID(float *kp, float *ki, float *kd)
{
    *kp = _kp;
    *ki = _ki;
    *kd = _kd;
}