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

EvoMotor::EvoMotor(MotorPort motorPort, MotorType motorType, bool motorFlip)
{
    switch (motorType)
    {
    case GENERICWITHENCODER:
        setParameters(motorPort, motorFlip, 4000, 100, true, 360, 5, 30);
        break;
    case GENERICWITHOUTENCODER:
        setParameters(motorPort, motorFlip, 4000, 100, false);
        break;
    case EV3LargeMotor:
        setParameters(motorPort, motorFlip, 4000, 100, true, 720, 5, 30);
        break;
    case EV3MediumMotor:
        setParameters(motorPort, motorFlip, 4000, 100, true, 720, 5, 30);
        break;
    case GeekServoDCMotor:
        setParameters(motorPort, motorFlip, 4000, 100, false);
        break;
    case ITERMKS:
        setParameters(motorPort, motorFlip, 4000, 500, true, 1204, 10, 50);
        break;
    case ITERMKT:
        setParameters(motorPort, motorFlip, 4000, 100, true, 1204, 10, 50);
        break;
    case EVOMotor300:
        setParameters(motorPort, motorFlip, 4000, 100, true, 2800, 10, 50);
        break;
    case EVOMotor100:
        setParameters(motorPort, motorFlip, 4000, 100, true, 8400, 10, 50);
        break;
    }

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

void EvoMotor::setParameters(MotorPort motorPort, bool motorFlip, int maxSpd, int minSpd, bool encoderAvailable, int countPerRevolution, float kp, float kd)
{
    _motorFlip = motorFlip;
    _motorPort = motorPort;
    _maxSpd = maxSpd;
    _minSpd = minSpd;
    _countPerRevolution = countPerRevolution;
    _encoderAvailable = encoderAvailable;
    _kp = kp;
    _kd = kd;
}

void EvoMotor::begin()
{
    driver.begin();
    if (_encoderAvailable())
    {
        encoder.detach();
        encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
        encoder.clearCount();
        setStallThresholds(50, 10);
    }

    setStopBehaviour(BRAKE);
    coast();

    xTaskCreate(motorControlTask, "Motor Control Task", 2048, this, 1, NULL);
}

void EvoMotor::flipEncoderDirection(bool flip)
{
    if (_encoderAvailable())
    {
        if (flip)
        {
            encoder.detach();
            encoder.attachFullQuad(_motorPins.tach2, _motorPins.tach1);
            encoder.clearCount();
        }
        else
        {
            encoder.detach();
            encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
            encoder.clearCount();
        }
    }
}

void EvoMotor::setSpeedLimit(int maxSpd, int minSpd)
{
    _maxSpd = maxSpd;
    _minSpd = minSpd;
}

void EvoMotor::getSpeedLimit(int *maxSpd, int *minSpd)
{
    *maxSpd = _maxSpd;
    *minSpd = _minSpd;
}

void EvoMotor::setEncoderAvailable(bool encoderAvailable)
{
    if (!_encoderAvailable() && encoderAvailable)
    {
        encoder.detach();
        encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
        encoder.clearCount();
        setStallThresholds(50, 10);
    }
    _encoderAvailable = encoderAvailable;
}

// Method to get encoder availability
bool EvoMotor::isEncoderAvailable()
{
    return _encoderAvailable;
}
// Method to set encoder count per revolution
void EvoMotor::setCountPerRevolution(int countPerRevolution)
{
    if (_encoderAvailable())
    {
        _countPerRevolution = countPerRevolution;
    }
}

// Method to get encoder count per revolution
int EvoMotor::getCountPerRevolution()
{
    if (_encoderAvailable())
    {
        return _countPerRevolution;
    }
    return 0;
}

// Method to get the encoder count
int EvoMotor::getCount()
{
    if (_encoderAvailable())
    {
        return encoder.getCount();
    }
    return 0;
}

// Method to set the encoder count
void EvoMotor::setCount(int count)
{
    if (_encoderAvailable())
    {
        encoder.setCount(count);
    }
    return 0;
}

// Method to reset the encoder count
void EvoMotor::resetCount()
{
    if (_encoderAvailable())
    {
        encoder.setCount(0);
    }
    return 0;
}

// Method to get current angle
int EvoMotor::getAngle()
{
    if (_encoderAvailable())
    {
        return encoder.getCount() * 360 / _countPerRevolution;
    }
    return 0;
}

// Method to reset angle
void EvoMotor::resetAngle()
{
    if (_encoderAvailable())
    {
        encoder.setCount(0);
    }
}

void EvoMotor::setAngle(int angle)
{
    if (_encoderAvailable())
    {
        encoder.setCount(angle * _countPerRevolution / 360);
    }
}

// Method returns if the motor is stalled
bool EvoMotor::isStalled()
{
    if (_encoderAvailable())
    {
        return _stalled;
    }
    return false;
}

// Method to set the motor stall thersholds
void EvoMotor::setStallThresholds(int timems, int angle)
{
    if (_encoderAvailable())
    {
        _stallTime = timems;
        _stallCountThreshold = angle;
    }
}

// Method to stop the motor
void EvoMotor::setStopBehaviour(MotorState motorStopState)
{
    if (!_encoderAvailable() && motorStopState == TARGET)
    {
        return;
    }
    _motorStopState = motorStopState;
}

// Method to stop the motor using motorStopState
void EvoMotor::stop()
{
    switch (_motorStopState)
    {
    case BRAKE:
        brake();
        break;
    case COAST:
        coast();
        break;
    case HOLD:
        if (_encoderAvailable())
        {
            hold();
        }
        else
        {
            brake();
        }
        break;
    default:
        brake();
    }
}
// Method to stop the motor
void EvoMotor::coast()
{
    this->_motorState = COAST;
}

// Method to brake the motor
void EvoMotor::brake()
{
    this->_motorState = BRAKE;
    driver.setPWM(_motorPins.power1, 4096, 0);
    driver.setPWM(_motorPins.power2, 4096, 0);
}

void EvoMotor::hold()
{
    if (_encoderAvailable())
    {
        this->runTarget(_maxSpd, this->getAngle());
    }
    else
    {
        brake();
    }
}

void EvoMotor::move(int speed)
{
    speed = clamp(speed, _maxSpd * -1, _maxSpd);

    if (speed > 0)
    {
        speed = clamp(speed, _minSpd, _maxSpd);
    }
    else if (speed < 0)
    {
        speed = clamp(speed, _maxSpd * -1, _minSpd * -1);
    }

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

void EvoMotor::runCount(int speed, int count)
{
    if (_encoderAvailable())
    {
        this->resetCount();
        this->run(speed);
        while (abs(this->getCount()) < abs(count))
            vTaskDelay(1);
        ;
        this->stop();
    }
}

// Method to run the motor for a specified number of degrees
void EvoMotor::runAngle(int speed, int angle)
{
    if (_encoderAvailable())
    {
        this->resetAngle();
        this->run(speed);
        while (abs(this->getAngle()) < abs(angle))
            vTaskDelay(1);
        ;
        this->stop();
    }
}

void EvoMotor::runTime(int speed, int timeMS)
{
    this->run(speed);
    int timeNow = millis();
    while ((millis() - timeNow) < timeMS)
    {
        this->run(speed);
        vTaskDelay(10);
    }
    this->stop();
}

void EvoMotor::runTarget(int speed, int angle, bool blocking)
{
    if (_encoderAvailable())
    {
        this->_targetSpeed = speed;
        this->_targetAngle = angle;
        this->_completed = false;
        this->_motorState = TARGET;
        if (blocking)
        {
            while (abs(this->getAngle() - this->_targetAngle) > 2)
            {
                vTaskDelay(1);
            }
        }
    }
}

void EvoMotor::runUntilStalled(int speed)
{
    if (_encoderAvailable())
    {
        this->run(speed);
        delay(_stallTime * 2);
        _stalled = false;
        while (!this->_stalled)
        {
            vTaskDelay(1);
        }
        this->stop();
    }
}

void EvoMotor::motorControlTask(void *parameter)
{
    EvoMotor *motor = static_cast<EvoMotor *>(parameter);
    int _motorSpeed;
    int _error, _perror = 0;
    int encoder, prevencoder = 0, lastreadtime = 0;
    int _measuredSpeed;
    int timeNow, lastReadTime = 0;
    for (;;)
    {
        encoder = motor->getAngle();
        switch (motor->_motorState)
        {
        case BRAKE:
            break;
        case TARGET:
            _error = encoder - motor->_targetAngle;

            _motorSpeed = clamp(_error * motor->_kp * -1 + (_error - _perror) * motor->_kd, motor->_targetSpeed * -1, motor->_targetSpeed);
            motor->move(_motorSpeed);
            _perror = _error;
            break;
        case COAST:
            motor->move(0);
            break;
        case RUN:
            timeNow = millis();
            if ((timeNow - lastReadTime) > motor->_stallTime)
            {
                if (abs(encoder - prevencoder) < motor->_stallCountThreshold)
                {
                    motor->_stalled = true;
                }
                else
                {
                    motor->_stalled = false;
                }
                lastReadTime = timeNow;
                prevencoder = encoder;
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