#include <Arduino.h>
#include <Evo.h>

#if defined(EVO_BOARD_X1E)
EvoX1E evo;
#elif defined(EVO_BOARD_X1P)
EvoX1P evo;
#endif

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
