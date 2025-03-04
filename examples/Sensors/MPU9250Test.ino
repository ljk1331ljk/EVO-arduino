#include <EvoIMU.h> // Include the EvoIMU library

EvoIMU mpu(10); // Assuming CS pin is 10

void setup() {
    Serial.begin(9600);
    if (!mpu.begin()) {
        Serial.println("Failed to initialize the EvoIMU sensor!");
        while (1); // Halt if initialization fails
    }
    Serial.println("EvoIMU sensor initialized successfully.");
}

void loop() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.readAccelerometer(&ax, &ay, &az);
    mpu.readGyroscope(&gx, &gy, &gz);
    
    Serial.print("Accelerometer: ");
    Serial.print("X: "); Serial.print(ax);
    Serial.print(", Y: "); Serial.print(ay);
    Serial.print(", Z: "); Serial.println(az);
    
    Serial.print("Gyroscope: ");
    Serial.print("X: "); Serial.print(gx);
    Serial.print(", Y: "); Serial.print(gy);
    Serial.print(", Z: "); Serial.println(gz);
    
    // Use evo.writeToDisplay to show the data on the display
    evo.writeToDisplay("Accel: X:", ax, ay, az);
    evo.writeToDisplay("Gyro: X:", gx, gy, gz);
    
    delay(1000); // Delay for readability
}
