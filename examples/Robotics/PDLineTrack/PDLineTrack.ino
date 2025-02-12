#include <EvoMotorPair.h>
#include <EvoTrace.h>

EVO evo;
EvoMotor motorLeft(M2, true);
EvoMotor motorRight(M3);
EvoMotorPair robot(&motorLeft, &motorRight);
EvoTCS34725 sensorLeft(I2C1);
EvoTCS34725 sensorRight(I2C2);

// Create an instance of EvoTrace
EvoTrace trace(&sensorLeft, &sensorRight, &motorLeft, &motorRight);

void setup() {
    evo.begin();
    Serial.begin(115200); // Initialize Serial communication
    trace.begin();  // Initialize the trace object

    trace.PDTrackDegrees(1500, 2, 10, 2000);
    trace.PDTrackJunction(1500, 2, 10, 15, 1);
    delay(500);
    robot.coast();
}


void loop() {
    trace.readSensors(); // Read sensor values
    trace.displaySensorValues(evo); // Display sensor values on the EVO display
}
