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
        setParameters(motorPort, motorFlip, -4000, 4000, true, 360, 5, 30, 30);
        break;
    case GENERISWITHOUTENCODER:
        setParameters(motorPort, motorFlip, -4000, 4000, false);
        break;
    case EV3LargeMotor:
        setParameters(motorPort, motorFlip, -4000, 4000, true, 720, 5, 30, 30);
        break;
    case EV3MediumMotor:
        setParameters(motorPort, motorFlip, -4000, 4000, true, 720, 5, 30, 30);
        break;
    case GeekServoDCMotor:
        setParameters(motorPort, motorFlip, -4000, 4000, false);
        break;
    case ITERSpeed:
        setParameters(motorPort, motorFlip, -4000, 4000, true, 1204, 5, 30, 30);
        break;
    case ITERTorque:
        setParameters(motorPort, motorFlip, -4000, 4000, true, 1204, 5, 30, 30);
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

void EvoMotor::setParameters(MotorPort motorPort, bool motorFlip, int minSpeed, int maxSpeed, bool encoderAvailable, int countPerRevolution, float kp, float ki, float kd)
{
    _motorFlip = motorFlip;
    _motorPort = motorPort;
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
    _countPerRevolution = countPerRevolution;
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _encoderAvailable = encoderAvailable;
}

void EvoMotor::begin()
{
    driver.begin();
    driver.setPWM(_motorPins.power1, 0, 4096);
    driver.setPWM(_motorPins.power2, 0, 4096);
    setStopBehaviour(BRAKE);
    setStallThresholds(50, 10);
    encoder.attachFullQuad(_motorPins.tach1, _motorPins.tach2);
    encoder.clearCount();
    xTaskCreate(motorControlTask, "Motor Control Task", 2048, this, 1, NULL);
}

void EvoMotor::setSpeedLimit(int minSpeed, int maxSpeed)
{
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
}

void EvoMotor::getSpeedLimit(int *minSpeed, int *maxSpeed)
{
    *minSpeed = _minSpeed;
    *maxSpeed = _maxSpeed;
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

void EvoMotor::setAngle(int angle)
{
    encoder.setCount(angle * _countPerRevolution / 360);
}

// Method returns if the motor is stalled
bool EvoMotor::isStalled()
{
    return _stalled;
}

// Method to set the motor stall thersholds
void EvoMotor::setStallThresholds(int timems, int count)
{
    _stallTime = timems;
    _stallCountThreshold = count;
}

// Method to stop the motor
void EvoMotor::setStopBehaviour(MotorState motorStopState)
{
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
        hold();
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
    this->run(speed);
    while (abs(this->getAngle()) < angle)
        vTaskDelay(1);
    ;
    this->stop();
}

void EvoMotor::runTime(int speed, int timeMS)
{
    this->run(speed);
    int timeNow = millis();
    while ((millis() - timeNow) < timeMS)
    {
        vTaskDelay(1);
    }
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
        while ((abs(this->getAngle()) - this->_targetAngle) < 2)
        {
            vTaskDelay(1);
        }
    }
}

void EvoMotor::runUntilStalled(int speed)
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

void EvoMotor::motorControlTask(void *parameter)
{
    EvoMotor *motor = static_cast<EvoMotor *>(parameter);
    int _motorSpeed;
    int _error;
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
            _motorSpeed = clamp(_error * motor->_kp * -1, motor->_targetSpeed * -1, motor->_targetSpeed);
            motor->move(_motorSpeed);
            break;
        case COAST:
            motor->move(0);
            break;
        case RUN:
            timeNow = millis();
            if ((timeNow - lastReadTime) > motor->_stallTime)
            {
                Serial.print(abs(encoder - prevencoder));
                Serial.print(" ");
                Serial.print(motor->_stallCountThreshold);
                Serial.print(" ");
                Serial.println(motor->_stalled);
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