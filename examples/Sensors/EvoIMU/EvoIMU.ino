#include "Evo.h"

// Create an EvoIMU object using the default I2C channel
EVOX1 evo;
EvoIMU imu(I2C1);

float ax, ay, az, aSqrt, gx, gy, gz, mDirection, mx, my, mz; // Magnetometer values

void setup() {
  Serial.begin(115200);
  evo.begin();
  imu.begin();
  evo.writeToDisplay("IMU Sensor Test", 0, 0, true, false);
  evo.writeToDisplay("Battery:", 0, 16);
  evo.writeToDisplay(evo.getBattery(), 50, 16, false, true);
  evo.waitForButton();
}

void loop() {
  imu.getAccelerometer(&ax, &ay, &az, &aSqrt);
  imu.getGyroscope(&gx, &gy, &gz);
  imu.getMagnetometer(&mx, &my, &mz, &mDirection);

  evo.clearDisplay();
  evo.writeToDisplay("Accel:", 0, 0);
  evo.writeToDisplay(int(ax), 35, 0);
  evo.writeToDisplay(int(ay), 58, 0);
  evo.writeToDisplay(int(az), 81, 0);
  evo.writeToDisplay(int(aSqrt), 104, 0);
  evo.writeToDisplay("Gyro:", 0, 16); 
  evo.writeToDisplay(int(gx), 35, 16);
  evo.writeToDisplay(int(gy), 58, 16);
  evo.writeToDisplay(int(gz), 81, 16);
  evo.writeToDisplay("Mag:", 0, 32);
  evo.writeToDisplay(int(mx), 35, 32);
  evo.writeToDisplay(int(my), 58, 32);
  evo.writeToDisplay(int(mz), 81, 32);
  evo.writeToDisplay(int(mDirection), 104, 0);
  evo.drawDisplay();
}
