#include "EvoHuskyLens.h"

void EvoHuskyLens::begin()
{
    i2CDevice.selectChannel(_channel);
    if (!huskylens.begin(Wire))
    {
        Serial.println(F("Failed to boot HuskyLens"));
    }
    setMode(ALGORITHM_COLOR_RECOGNITION);
}

void EvoHuskyLens::setMode(protocolAlgorithm algorithmType)
{
    i2CDevice.selectChannel(_channel);
    huskylens.writeAlgorithm(algorithmType);
    _algorithmType = algorithmType;
}

bool EvoHuskyLens::requestBlocks(HUSKYLENSResult *result, int16_t ID)
{
    i2CDevice.selectChannel(_channel);
    if (_algorithmType == ALGORITHM_LINE_TRACKING)
        return false;
    if (ID == 0)
    {
        if (!huskylens.requestBlocks())
            return false;
        else if (!huskylens.isLearned())
            return false;
        else if (!huskylens.available())
            return false;
        else
        {
            result = huskylens.read();
        }
    }
    else
    {
        if (!huskylens.requestBlocks(ID))
            return false;
        else if (!huskylens.isLearned())
            return false;
        else if (!huskylens.available())
            return false;
        else
        {
            result = huskylens.read();
        }
    }
    return true;
}

bool EvoHuskyLens::requestArrows(HUSKYLENSResult *result, int16_t ID)
{
    i2CDevice.selectChannel(_channel);
    if (_algorithmType != ALGORITHM_LINE_TRACKING)
        return false;

    if (!huskylens.requestArrows())
        return false;
    else
    {
        result = huskylens.read();
    }
    return true;
}

bool EvoHuskyLens::writeString(String text, uint16_t x, uint8_t y)
{
    i2CDevice.selectChannel(_channel);
    huskylens.customText(text, x, y);
}
bool EvoHuskyLens::clearScreen()
{
    i2CDevice.selectChannel(_channel);
    huskylens.clearCustomText();
}

void EvoHuskyLens::printResult(HUSKYLENSResult result)
{
    if (result.command == COMMAND_RETURN_BLOCK)
    {
        Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW)
    {
        Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
    }
    else
    {
        Serial.println("Object unknown!");
    }
}