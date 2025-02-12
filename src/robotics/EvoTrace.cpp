#include "EvoTrace.h"

EvoTrace::EvoTrace(EvoTCS34725* leftSensor, EvoTCS34725* rightSensor, EvoMotor* leftMotor, EvoMotor* rightMotor)
    : sensorLeft(leftSensor), sensorRight(rightSensor), motorLeft(leftMotor), motorRight(rightMotor) {}

void EvoTrace::begin() {    
    sensorLeft->begin();
    sensorRight->begin();
    motorLeft->begin();
    motorRight->begin();
}

void EvoTrace::readSensors() {
    sensorLeft->getRawRGBC(&lr, &lg, &lb, &lc);
    sensorRight->getRawRGBC(&rr, &rg, &rb, &rc);
}

void EvoTrace::displaySensorValues(EVO& evo) { 
    evo.clearDisplay();
    
    // Display left sensor values
    evo.writeToDisplay("Left:", 0, 0);
    evo.writeToDisplay(int(lr), 40, 0); 
    evo.writeToDisplay(int(lg), 60, 0); 
    evo.writeToDisplay(int(lb), 80, 0); 
    evo.writeToDisplay(int(lc), 100, 0); 

    // Display right sensor values
    evo.writeToDisplay("Right:", 0, 8);
    evo.writeToDisplay(int(rr), 40, 8); 
    evo.writeToDisplay(int(rg), 60, 8); 
    evo.writeToDisplay(int(rb), 80, 8); 
    evo.writeToDisplay(int(rc), 100, 8);
    
    evo.drawDisplay();
}

void EvoTrace::PDTrackOn(int speed, float kp, float kd, int mode, int ThV) {
    sensorLeft->getRawRGBC(&lr, &lg, &lb, &lc);
    sensorRight->getRawRGBC(&rr, &rg, &rb, &rc);

    if (mode == 1) {
        error = lc - ThV;                   // Calculate error based on clear values
    }

    else if (mode == 2) {
        error = ThV - lc;                   // Calculate error based on clear values
    }

    else if (mode == 3) {
        error = lc - rc;                    // Calculate error based on clear values
    }

    else if (mode == 4) {
        error = rc - ThV;                   // Calculate error based on clear values
    }

    else if (mode == 5) {
        error = ThV - rc;                   // Calculate error based on clear values
    }

    P = error * kp;                         // Proportional control
    D = (error - prevError) * kd;           // Derivative control
    
    // Move motors based on PD control
    motorLeft->run(speed + P + D);
    motorRight->run(speed - (P + D));
    
    prevError = error;                      // Update previous error
}

void EvoTrace::PDTrackDegrees(int speed, float kp, float kd, int degrees, int mode, int ThV, bool brake) {
    motorLeft->resetAngle(); // Reset the angle for the left motor
    motorRight->resetAngle(); // Reset the angle for the right motor
    
    while ((abs(motorLeft->getAngle()) + abs(motorRight->getAngle())) / 2 < degrees) {
        sensorLeft->getRawRGBC(&lr, &lg, &lb, &lc);
        sensorRight->getRawRGBC(&rr, &rg, &rb, &rc);

        if (mode == 1) {
            error = lc - ThV;                // Calculate error based on clear values
        }

        else if (mode == 2) {
            error = ThV - lc;                // Calculate error based on clear values
        }

        else if (mode == 3) {
            error = lc - rc;                // Calculate error based on clear values
        }

        else if (mode == 4) {
            error = rc - ThV;                // Calculate error based on clear values
        }

        else if (mode == 5) {
            error = ThV - rc;                // Calculate error based on clear values
        }

        P = error * kp;                      // Proportional control
        D = (error - prevError) * kd;        // Derivative control
        
        // Move motors based on PD control
        motorLeft->run(speed + P + D);
        motorRight->run(speed - (P + D));
        
        prevError = error;                  // Update previous error
    }
    
    if (brake) {
        motorLeft->brake();
        motorRight->brake();
    }
}

void EvoTrace::PDTrackJunction(int speed, float kp, float kd, int threshold, int maxJunctions, int mode, int ThV, bool brake) {
    int junctionCount = 0; // Initialize junction counter
    bool atJunction = false; // State variable to track junction detection

    while (junctionCount < maxJunctions) {
        // Read sensor values
        sensorLeft->getRawRGBC(&lr, &lg, &lb, &lc);
        sensorRight->getRawRGBC(&rr, &rg, &rb, &rc);

        // Check if both Sensors are below the threshold (Both on black)
        if (lc < threshold && rc < threshold)   atJunction = true;
        
        // If we were at a junction, we can increment the counter
        if (atJunction) {
            junctionCount++;
            atJunction = false; // Reset the junction state 

            if (junctionCount < maxJunctions) {
                delay(500);
            }
        }

        // Calculate error based on clear values
        if (mode == 1) {
            error = lc - ThV;                // Calculate error based on clear values
        }

        else if (mode == 2) {
            error = ThV - lc;                // Calculate error based on clear values
        }

        else if (mode == 3) {
            error = lc - rc;                // Calculate error based on clear values
        }

        else if (mode == 4) {
            error = rc - ThV;                // Calculate error based on clear values
        }

        else if (mode == 5) {
            error = ThV - rc;                // Calculate error based on clear values
        }

        P = error * kp;                     // Proportional control
        D = (error - prevError) * kd;       // Derivative control
        
        // Move motors based on PD control
        motorLeft->run(speed + P + D);
        motorRight->run(speed - (P + D));
        
        prevError = error;                  // Update previous error
    } 

    // If brake is true, stop the motors
    if (brake) {
        motorLeft->brake();
        motorRight->brake();
    }
}