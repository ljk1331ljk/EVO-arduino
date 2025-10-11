#include "EvoMotor.h"

EvoMotor::EvoMotor(MotorPort motorPort, MotorType motorType, bool motorFlip)
{
    switch (motorType)
    {
    case GENERICWITHENCODER:
        setParameters(motorPort, !motorFlip, 4000, 100, 150, 700, true, 360);
        break;
    case GENERICWITHOUTENCODER:
        setParameters(motorPort, !motorFlip, 4000, 100, 0, 0, false);
        break;
    case EV3LargeMotor:
        setParameters(motorPort, !motorFlip, 4000, 100, 150, 700, true, 720);
        break;
    case EV3MediumMotor:
        setParameters(motorPort, motorFlip, 4000, 150, 150, 700, true, 720);
        break;
    case GeekServoDCMotor:
        setParameters(motorPort, motorFlip, 4000, 100, 0, 0, false);
        break;
    case ITERMK495:
        setParameters(motorPort, !motorFlip, 4000, 500, 10, 50, true, 1204);
        break;
    case ITERMK330:
        setParameters(motorPort, !motorFlip, 4000, 100, 10, 50, true, 1807);
        break;
    case ITERMK195:
        setParameters(motorPort, !motorFlip, 4000, 100, 10, 50, true, 2988);
        break;
    case EVOMotor300:
        setParameters(motorPort, !motorFlip, 4000, 100, 150, 700, true, 2800);
        break;
    case EVOMotor100:
        setParameters(motorPort, !motorFlip, 4000, 100, 150, 700, true, 8400);
        break;
    }

    switch (_motorPort)
    {
    case M1:
        if (_motorFlip)
            _motorPins = {MOTOR11, MOTOR12, TACH12, TACH11};
        else
            _motorPins = {MOTOR12, MOTOR11, TACH11, TACH12};
        break;
    case M2:
        if (_motorFlip)
            _motorPins = {MOTOR22, MOTOR21, TACH22, TACH21};
        else
            _motorPins = {MOTOR21, MOTOR22, TACH21, TACH22};
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

void EvoMotor::setParameters(MotorPort motorPort, bool motorFlip, int maxSpd, int minSpd, float kp, float kd, bool encoderAvailable, int countPerRevolution)
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
    encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
    encoder.clearCount();

    setStopBehaviour(BRAKE);
    setStallThreshold(360);

    xTaskCreate(motorControlTask, "Motor Control Task", 2048, this, 1, &motorTaskHandle);
    xTaskCreate(motorSpeedTask, "Motor Speed Task", 1024, this, 1, NULL);

    coast();
}

void EvoMotor::flipEncoderDirection(bool flip)
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
    _countPerRevolution = countPerRevolution;
}

// Method to get encoder count per revolution
int EvoMotor::getCountPerRevolution()
{
    return _countPerRevolution;
}

// Method to get the encoder count
int EvoMotor::getCount()
{
    return encoder.getCount();
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

// Method to set angle
void EvoMotor::setAngle(int angle)
{
    encoder.setCount(angle * _countPerRevolution / 360);
}

// Method returns if the motor is stalled
bool EvoMotor::isStalled()
{
    return this->getSpeed() < this->_stallThreshold;
}

// Method to set the motor stall thersholds
void EvoMotor::setStallThreshold(int threshold)
{
    _stallThreshold = threshold;
}

// Method to stop the motor
void EvoMotor::setStopBehaviour(MotorStop motorStopState)
{
    _motorStopBehaviour = motorStopState;
}

// Method to stop the motor using motorStopState
void EvoMotor::stop()
{
    switch (_motorStopBehaviour)
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
}

// Method to stop the motor
void EvoMotor::coast()
{
    this->pauseMotorTask();
    this->move(0);
}

// Method to brake the motor
void EvoMotor::brake()
{
    this->pauseMotorTask();
    driver.setPWM(_motorPins.power1, 4096, 0);
    driver.setPWM(_motorPins.power2, 4096, 0);
}

void EvoMotor::hold()
{
    this->_targetValue = this->getAngle();
    this->_targetSpeed = this->_holdPower;
    this->_runMode = runMode::HOLDPOS;
    this->resumeMotorTask();
}
void EvoMotor::setHoldPower(uint16_t power)
{
    this->_holdPower = power;
}

void EvoMotor::move(int speed)
{
    speed = constrain(speed, -4095, 4095);
    driver.setPWMFreq(2500);
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
        driver.setPWM(_motorPins.power1, 0, 0);
        driver.setPWM(_motorPins.power2, 0, 0);
    }
}

void EvoMotor::run(int speed)
{
    this->pauseMotorTask();
    this->move(speed);
}

void EvoMotor::runCount(int speed, int count, bool blocking)
{
    if (blocking)
    {
        this->pauseMotorTask();
        this->resetCount();
        this->move(speed);
        while (abs(this->getCount()) < abs(count))
            vTaskDelay(1);
        this->stop();
    }
    else
    {
        this->_targetValue = count;
        this->_targetSpeed = speed;
        this->_runMode = runMode::COUNT;
        this->resumeMotorTask();
    }
}

// Method to run the motor for a specified number of degrees
void EvoMotor::runAngle(int speed, int angle, bool blocking)
{
    if (blocking)
    {
        this->pauseMotorTask();
        this->resetAngle();
        this->move(speed);
        while (abs(this->getAngle()) < abs(angle))
            vTaskDelay(1);
        this->stop();
    }
    else
    {
        this->_targetValue = angle;
        this->_targetSpeed = speed;
        this->_runMode = runMode::ANGLE;
        this->resumeMotorTask();
    }
}

void EvoMotor::runTime(int speed, int timeMS, bool blocking)
{
    if (blocking)
    {
        this->pauseMotorTask();
        this->move(speed);
        vTaskDelay(timeMS / portTICK_PERIOD_MS);
        this->stop();
    }
    else
    {
        this->_targetValue = timeMS;
        this->_targetSpeed = speed;
        this->_runMode = runMode::TIME;
        this->resumeMotorTask();
    }
}

void EvoMotor::runTarget(int speed, int angle, MotorStop then, bool blocking)
{
    if (blocking)
    {
        int count = 0;
        int _error = 0, _previousError = 0;
        int _motorSpeed;
        while (true)
        {
            _error = angle - this->getAngle();
            _motorSpeed = _error * _kp + (_error - _previousError) * _kd;
            _motorSpeed = constrain(_motorSpeed, 0 - speed, speed);
            this->move(_motorSpeed);
            _previousError = _error;
            if (abs(this->getAngle() - angle) < 3)
            {

                count++;
                if (count > 10)
                    break;
            }
            else
            {
                count = 0;
            }
            vTaskDelay(1);
        }
        switch (then)
        {
        case BRAKE:
            this->brake();
            break;
        case COAST:
            this->coast();
            break;
        case HOLD:
            this->hold();
            break;
        default:
            break;
        }
    }
    else
    {
        this->_targetSpeed = speed;
        this->_targetValue = angle;
        this->_targetThen = then;
        this->_runMode = runMode::TARGET;
        this->resumeMotorTask();
    }
}

void EvoMotor::setTargetPD(float kp, float kd)
{
    _kp = kp;
    _kd = kd;
}

void EvoMotor::getTargetPD(float *kp, float *kd)
{
    *kp = _kp;
    *kd = _kd;
}

void EvoMotor::runUntilStalled(int speed, bool blocking)
{
    if (blocking)
    {
        this->pauseMotorTask();
        this->move(speed);
        delay(300);
        while (this->getSpeed() > _stallThreshold)
        {
            vTaskDelay(1);
        }
        this->stop();
    }
    else
    {
        this->_targetSpeed = speed;
        this->_runMode = runMode::STALLED;
        this->resumeMotorTask();
    }
}

void EvoMotor::pauseMotorTask()
{
    if (!this->motorTaskSuspended)
    {
        vTaskSuspend(this->motorTaskHandle);
        this->motorTaskSuspended = true;
    }
}

void EvoMotor::resumeMotorTask()
{
    if (this->motorTaskSuspended)
    {
        vTaskResume(this->motorTaskHandle);
        this->motorTaskSuspended = false;
    }
}

void EvoMotor::motorControlTask(void *parameter)
{
    EvoMotor *motor = static_cast<EvoMotor *>(parameter);
    int _motorSpeed;
    int timeNow;
    int count = 0;
    int _error = 0, _previousError = 0;
    for (;;)
    {
        switch (motor->_runMode)
        {
        case runMode::NONE:
            break;
        case runMode::TIME:
            motor->resetAngle();
            motor->move(motor->_targetSpeed);
            timeNow = millis();
            while ((millis() - timeNow) < motor->_targetValue)
                vTaskDelay(1);
            motor->stop();
            motor->pauseMotorTask();
            break;
        case runMode::ANGLE:
            motor->resetAngle();
            motor->move(motor->_targetSpeed);
            while (abs(motor->getAngle()) < abs(motor->_targetValue))
                vTaskDelay(1);
            motor->stop();
            motor->pauseMotorTask();
            break;
        case runMode::COUNT:
            motor->resetCount();
            motor->move(motor->_targetSpeed);
            while (abs(motor->getCount()) < abs(motor->_targetValue))
                vTaskDelay(1);
            motor->stop();
            motor->pauseMotorTask();
            break;
        case runMode::TARGET:
            count = 0;
            _error = 0;
            _previousError = 0;
            for (;;)
            {
                _error = motor->_targetValue - motor->getAngle();
                _motorSpeed = _error * motor->_kp + (_error - _previousError) * motor->_kd;
                _motorSpeed = constrain(_motorSpeed, 0 - motor->_targetSpeed, motor->_targetSpeed);
                motor->move(_motorSpeed);
                _previousError = _error;
                if (abs(motor->getAngle() - motor->_targetValue) < 3)
                {
                    count++;
                    if (count > 10)
                    {
                        break;
                    }
                }
                else
                {
                    count = 0;
                }
                vTaskDelay(1);
            }
            switch (motor->_targetThen)
            {
            case BRAKE:
                motor->brake();
                motor->pauseMotorTask();
                break;
            case COAST:
                motor->coast();
                motor->pauseMotorTask();
                break;
            case HOLD:
                motor->_runMode = runMode::HOLDPOS;
                break;
            default:
                break;
            }
            break;
        case runMode::STALLED:
            motor->move(motor->_targetSpeed);
            delay(300);
            while (motor->getSpeed() > motor->_stallThreshold)
            {
                vTaskDelay(1);
            }
            motor->stop();
            motor->pauseMotorTask();
        case runMode::HOLDPOS:
            _error = motor->_targetValue - motor->getAngle();
            _motorSpeed = _error * motor->_kp + (_error - _previousError) * motor->_kd;
            _motorSpeed = constrain(_motorSpeed, 0 - motor->_targetSpeed, motor->_targetSpeed);
            motor->move(_motorSpeed);
            _previousError = _error;
            vTaskDelay(1);
            break;
        }

        vTaskDelay(10);
    }
}

void EvoMotor::motorSpeedTask(void *parameter)
{
    EvoMotor *motor = static_cast<EvoMotor *>(parameter);
    long lastEncoder = 0, currentEncoder = 0;
    for (;;)
    {
        currentEncoder = motor->getAngle();
        motor->_measuredSpeed = (currentEncoder - lastEncoder) * 10;
        lastEncoder = currentEncoder;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

int EvoMotor::getSpeed()
{
    return this->_measuredSpeed;
}