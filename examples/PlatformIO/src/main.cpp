#include <Arduino.h>
#include <Evo.h>

#if defined(EVO_BOARD_X1E)
EvoX1E evo;
#elif defined(EVO_BOARD_X1P)
EvoX1P evo;
#endif

// Compile-only coverage for the public motor API. This function is never
// called, so opening this example cannot unexpectedly move connected motors.
[[maybe_unused]] static void verifyMotorApi()
{
    EvoMotor motor(M1, GENERICWITHOUTENCODER);
    motor.setSpeedLimit(2000, 100);
    motor.setStopBehaviour(BRAKE);
    motor.setEncoderAvailable(false);
    motor.run(0);
    motor.coast();

    EvoMotor secondMotor(M2, GENERICWITHOUTENCODER);
    EvoMotorPair motorPair(&motor, &secondMotor);
    (void)motorPair.hasIMU();
    motorPair.setAccelerationProfile(AccelerationProfile::SCurve);
    (void)motorPair.getAccelerationProfile();
    motorPair.setAccelerationProfile(AccelerationProfile::Trapezoidal);

    EvoServo servo(SERVO1);
    servo.setRange(0, 180);
    servo.setPulse(300, 1200);
    servo.write(90);
}

// Compile-only coverage for battery readings. This function is not called,
// so it does not communicate with the charger in the example.
[[maybe_unused]] static void verifyBatteryApi()
{
    (void)evo.getBattery();
    (void)evo.getTopBattery();
    (void)evo.getBottomBattery();
}

// Compile-only coverage for the onboard button API. The waits are never
// executed, so the example does not block during startup.
[[maybe_unused]] static void verifyButtonApi()
{
    (void)evo.getButton();
    (void)evo.getButton(1);
    evo.waitForButton();
    evo.waitForPress(20);
    evo.waitForRelease(20);
    evo.waitForBump(20);
    evo.waitForPress(1, 20);
    evo.waitForRelease(1, 20);
    evo.waitForBump(1, 20);
}

// Compile-only coverage for I2C channel selection and scanning. This function
// is never called, so it does not probe the bus during startup.
[[maybe_unused]] static void verifyI2CApi()
{
    uint8_t addresses[5];
    (void)evo.selectI2CChannel(I2C1);
    (void)evo.scanI2CChannel(I2C1, addresses, 5);
}

void setup()
{
    Serial.begin(115200);
    evo.begin();

    Serial.println();
    Serial.print("EVO library: ");
    Serial.println(EVO_LIBRARY_VERSION);
    Serial.print("Controller: ");
    Serial.println(evo.getControllerName());
    Serial.print("Motors: ");
    Serial.println(evo.getMotorCount());
    Serial.print("Servos: ");
    Serial.println(evo.getServoCount());

    if (evo.hasBuzzer())
    {
        evo.playTone(880, 100);
    }

    if (evo.hasDisplay())
    {
        evo.clearDisplay();
        evo.writeLineToDisplay(evo.getControllerName(), 0);
        evo.writeLineToDisplay(EVO_LIBRARY_VERSION, 1);
        evo.drawDisplay();
    }
}

void loop()
{
}
