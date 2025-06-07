#include "EvoTrace.h"

EvoTrace::EvoTrace(EvoTCS34725 *leftSensor, EvoTCS34725 *rightSensor, EvoMotor *leftMotor, EvoMotor *rightMotor)
{
    _leftSensor = leftSensor;
    _rightSensor = rightSensor;
    _leftMotor = leftMotor;
    _rightMotor = rightMotor;
}

void EvoTrace::begin()
{
    _leftSensor->begin();
    _rightSensor->begin();
    _leftMotor->begin();
    _rightMotor->begin();
}

void EvoTrace::PDTrackOn(int speed, float kp, float kd, int mode, int ThV)
{
    _leftSensor->getRawRGBC(&lr, &lg, &lb, &lc);
    _rightSensor->getRawRGBC(&rr, &rg, &rb, &rc);

    if (mode == 1)
    {
        error = lc - ThV; // Calculate error based on clear values
    }

    else if (mode == 2)
    {
        error = ThV - lc; // Calculate error based on clear values
    }

    else if (mode == 3)
    {
        error = lc - rc; // Calculate error based on clear values
    }

    else if (mode == 4)
    {
        error = rc - ThV; // Calculate error based on clear values
    }

    else if (mode == 5)
    {
        error = ThV - rc; // Calculate error based on clear values
    }

    P = error * kp;               // Proportional control
    D = (error - prevError) * kd; // Derivative control

    // Move motors based on PD control
    _leftMotor->run(speed + P + D);
    _rightMotor->run(speed - (P + D));

    prevError = error; // Update previous error
}

void EvoTrace::PDTrackDegrees(int speed, float kp, float kd, int degrees, int mode, int ThV, bool brake)
{
    _leftMotor->resetAngle();  // Reset the angle for the left motor
    _rightMotor->resetAngle(); // Reset the angle for the right motor

    while ((abs(_leftMotor->getAngle()) + abs(_rightMotor->getAngle())) / 2 < degrees)
    {
        _leftSensor->getRawRGBC(&lr, &lg, &lb, &lc);
        _rightSensor->getRawRGBC(&rr, &rg, &rb, &rc);

        if (mode == 1)
        {
            error = lc - ThV; // Calculate error based on clear values
        }

        else if (mode == 2)
        {
            error = ThV - lc; // Calculate error based on clear values
        }

        else if (mode == 3)
        {
            error = lc - rc; // Calculate error based on clear values
        }

        else if (mode == 4)
        {
            error = rc - ThV; // Calculate error based on clear values
        }

        else if (mode == 5)
        {
            error = ThV - rc; // Calculate error based on clear values
        }

        P = error * kp;               // Proportional control
        D = (error - prevError) * kd; // Derivative control

        // Move motors based on PD control
        _leftMotor->run(speed + P + D);
        _rightMotor->run(speed - (P + D));

        prevError = error; // Update previous error
    }

    if (brake)
    {
        _leftMotor->brake();
        _rightMotor->brake();
    }
}

void EvoTrace::PDTrackJunction(int speed, float kp, float kd, int threshold, int maxJunctions, int mode, int ThV, bool brake)
{
    int junctionCount = 0;   // Initialize junction counter
    bool atJunction = false; // State variable to track junction detection

    while (junctionCount < maxJunctions)
    {
        // Read sensor values
        _leftSensor->getRawRGBC(&lr, &lg, &lb, &lc);
        _rightSensor->getRawRGBC(&rr, &rg, &rb, &rc);

        // Check if both Sensors are below the threshold (Both on black)
        if (lc < threshold && rc < threshold)
            atJunction = true;

        // If we were at a junction, we can increment the counter
        if (atJunction)
        {
            junctionCount++;
            atJunction = false; // Reset the junction state

            if (junctionCount < maxJunctions)
            {
                delay(500);
            }
        }

        // Calculate error based on clear values
        if (mode == 1)
        {
            error = lc - ThV; // Calculate error based on clear values
        }

        else if (mode == 2)
        {
            error = ThV - lc; // Calculate error based on clear values
        }

        else if (mode == 3)
        {
            error = lc - rc; // Calculate error based on clear values
        }

        else if (mode == 4)
        {
            error = rc - ThV; // Calculate error based on clear values
        }

        else if (mode == 5)
        {
            error = ThV - rc; // Calculate error based on clear values
        }

        P = error * kp;               // Proportional control
        D = (error - prevError) * kd; // Derivative control

        // Move motors based on PD control
        _leftMotor->run(speed + P + D);
        _rightMotor->run(speed - (P + D));

        prevError = error; // Update previous error
    }

    // If brake is true, stop the motors
    if (brake)
    {
        _leftMotor->brake();
        _rightMotor->brake();
    }
}