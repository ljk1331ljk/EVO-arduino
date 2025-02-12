#ifndef EVO_TRACE_H
#define EVO_TRACE_H

#include <EvoTCS34725.h>
#include <EvoMotor.h>
#include <Evo.h>

class EvoTrace {
public:
    EvoTrace(EvoTCS34725* leftSensor, EvoTCS34725* rightSensor, EvoMotor* leftMotor, EvoMotor* rightMotor);
    void begin();
    void readSensors();
    void displaySensorValues(EVO& evo);

    void PDTrackOn(int speed, float kp, float kd, int mode, int ThV);
    void PDTrackDegrees(int speed, float kp, float kd, int degrees, int mode = 3, int Thv = 0, bool brake = true);
    void PDTrackJunction(int speed, float kp, float kd, int threshold, int maxJunctions, int mode = 3, int Thv = 0, bool brake = true);
    
private:
    EvoTCS34725* sensorLeft;
    EvoTCS34725* sensorRight;
    EvoMotor* motorLeft;
    EvoMotor* motorRight;
    
    uint16_t lr, lg, lb, lc;
    uint16_t rr, rg, rb, rc;

    int error, prevError = 0; // Initialize previous error
    float P, D; // Proportional and derivative variables
};

#endif