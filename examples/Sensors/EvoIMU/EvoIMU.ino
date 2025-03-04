#include <Evo.h> 

EVOX1 evo;
EvoIMU mpu(I2C1);
int16_t ax, ay, az, gx, gy, gz;

void setup() {
    Serial.begin(115200);
    evo.begin();
    mpu.begin();
    evo.writeToDisplay("IMU Test", 0, 0, true, false);
    evo.writeToDisplay("Battery:", 0, 16);
    evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
}

void loop() {
    mpu.readAccelerometer(&ax, &ay, &az); // Updated method call
    mpu.readGyroscope(&gx, &gy, &gz); // Updated method call

    evo.clearDisplay();
    evo.writeToDisplay("Accel", 0, 0);
    evo.writeToDisplay(int(ax), 35, 0);
    evo.writeToDisplay(int(ay), 58, 0);
    evo.writeToDisplay(int(az), 81, 0);
    evo.writeToDisplay("Gyro", 0, 16); 
    evo.writeToDisplay(int(gx), 35, 16);
    evo.writeToDisplay(int(gy), 58, 16);
    evo.writeToDisplay(int(gz), 81, 16);
    evo.drawDisplay();
}
