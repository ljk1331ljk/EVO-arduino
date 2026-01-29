#include <Evo.h>

EVOX1 evo;
EvoIMU imu(I2C1);

void setup()
{
    evo.begin();
    imu.begin();
    evo.writeToDisplay("Basic IMU Read", 0, 0, true, false);
    evo.writeToDisplay("Battery:", 0, 8);
    evo.writeToDisplay(evo.getBattery(), 50, 8, false, true);
    evo.waitForBump();
}

void loop()
{
    evo.clearDisplay();

    evo.writeToDisplay("X:", 0, 24);
    evo.writeToDisplay(imu.getEulerX(), 40, 24);

    evo.writeToDisplay("Y:", 0, 32);
    evo.writeToDisplay(imu.getEulerY(), 40, 32);

    evo.writeToDisplay("Z:", 0, 40);
    evo.writeToDisplay(imu.getEulerZ(), 40, 40);
    evo.drawDisplay();

    evo.writeToDisplay("Relative Heading:", 0, 48);
    evo.writeToDisplay(imu.getEulerZ(), 100, 48);
    evo.drawDisplay();
}
