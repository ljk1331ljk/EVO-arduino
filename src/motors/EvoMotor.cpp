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

EvoMotor::EvoMotor(MotorPort motorPort, bool motorFlip)
{
    _motorPort = motorPort;
    _motorFlip = motorFlip;
    switch (_motorPort)
    {
    case M1:
        if (!_motorFlip)
            motorPins = {MOTOR11, MOTOR12, TACH11, TACH12};
        else
            motorPins = {MOTOR12, MOTOR11, TACH12, TACH11};
        break;
    case M2:
        if (!_motorFlip)
            motorPins = {MOTOR22, MOTOR21, TACH21, TACH22};
        else
            motorPins = {MOTOR21, MOTOR22, TACH22, TACH21};
        break;
    case M3:
        if (!_motorFlip)
            motorPins = {MOTOR31, MOTOR32, TACH31, TACH32};
        else
            motorPins = {MOTOR32, MOTOR31, TACH32, TACH31};
        break;
    case M4:
        if (!_motorFlip)
            motorPins = {MOTOR41, MOTOR42, TACH41, TACH42};
        else
            motorPins = {MOTOR42, MOTOR41, TACH42, TACH41};
        break;
    }
}
void EvoMotor::begin()
{

    driver.begin();
    driver.setPWM(motorPins.power1, 0, 4096);
    driver.setPWM(motorPins.power2, 0, 4096);
    encoder.attachFullQuad(motorPins.tach1, motorPins.tach2);
    encoder.clearCount();
    xTaskCreate(motorControlTask, "Motor Control Task", 2048, this, 1, NULL);
}

void EvoMotor::move(int speed)
{
    speed = clamp(speed, -4000, 4000);
    if (speed > 0)
    {
        driver.setPWM(motorPins.power1, 0, speed);
        driver.setPWM(motorPins.power2, 0, 0);
    }
    else if (speed < 0)
    {
        driver.setPWM(motorPins.power1, 0, 0);
        driver.setPWM(motorPins.power2, 0, -speed);
    }
    else
    {
        driver.setPWM(motorPins.power1, 0, 4096);
        driver.setPWM(motorPins.power2, 0, 4096);
    }
}

void EvoMotor::run(int speed)
{
    this->motorState = RUN;
    this->move(speed);
    vTaskDelay(1 / portTICK_PERIOD_MS);
}
// Method to get current angle
int EvoMotor::getAngle()
{
    return encoder.getCount();
}

// Method to reset angle
void EvoMotor::resetAngle()
{
    encoder.setCount(0);
}

void EvoMotor::setAngle(int angle)
{
    encoder.setCount(angle);
}

// Method to stop the motor
void EvoMotor::coast()
{
    this->motorState = COAST;
}

// Method to brake the motor
void EvoMotor::brake()
{
    this->resetAngle();
    this->targetAngle = 0;
    this->motorState = BRAKE;
}

// Method to run the motor for a specified number of degrees
void EvoMotor::runDegrees(int speed, int degrees)
{
    this->motorState = RUN;
    this->resetAngle();
    while (abs(this->getAngle()) < degrees)
    {
        this->move(speed);
    }
    this->brake();
}

void EvoMotor::runTarget(int speed, int degrees, bool blocking)
{
    this->targetSpeed = speed;
    this->targetAngle = degrees;
    this->completed = false;
    this->motorState = TARGET;
    if (blocking)
    {
        while ((abs(this->getAngle()) - degrees) < 2)
            ;
    }
}

void EvoMotor::motorControlTask(void *parameter)
{
    EvoMotor *motor = (EvoMotor *)parameter;
    int motorSpeed;
    int error;
    for (;;)
    {
        int encoder = motor->getAngle();
        switch (motor->motorState)
        {
        case BRAKE:
            motor->move((encoder - motor->targetAngle) * -30);
            break;
        case TARGET:
            error = encoder - motor->targetAngle;
            motorSpeed = clamp(error * motor->_kp * -1, motor->targetSpeed * -1, motor->targetSpeed);
            motor->move(motorSpeed);
            break;
        case COAST:
            motor->move(0);
            break;
        case RUN:
            break;
        }
        vTaskDelay(1);
    }
}

void EvoMotor::setPID(float kp, float kd)
{
    _kp = kp;
    _kd = kd;
}