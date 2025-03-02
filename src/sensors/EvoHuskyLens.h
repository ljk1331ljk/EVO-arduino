#ifndef EVO_HUSKY_LENS_H
#define EVO_HUSKY_LENS_H

#include "../helper/EvoI2CDevice.h"
#include <HUSKYLENS.h>

class EvoHuskyLens
{
private:
    HUSKYLENS huskylens;
    I2CChannel _channel;
    I2CDevice &i2CDevice = I2CDevice::getInstance();
    protocolAlgorithm _algorithmType = ALGORITHM_COLOR_RECOGNITION;

public:
    EvoHuskyLens(I2CChannel channel)
    {
        _channel = channel;
    }
    void begin();

    /*
    ALGORITHM_FACE_RECOGNITION
    ALGORITHM_OBJECT_TRACKINGOBJECT
    ALGORITHM_OBJECT_RECOGNITION
    ALGORITHM_LINE_TRACKING
    ALGORITHM_COLOR_RECOGNITION
    ALGORITHM_TAG_RECOGNITION
    ALGORITHM_OBJECT_CLASSIFICATION
    */
    void setMode(protocolAlgorithm algorithmType);

    bool requestBlocks(HUSKYLENSResult *result, int16_t ID);
    bool requestArrows(HUSKYLENSResult *result, int16_t ID);
    // bool requestBlocksLearned();
    // bool requestArrowsLearned();
    // bool isLearned(int ID);
    // int16_t frameNumber();
    // int16_t countLearnedIDs();
    // int16_t countBlocks(int16_t ID);
    // int16_t countArrows(int16_t ID);

    bool writeString(String text, uint16_t x, uint8_t y);
    bool clearScreen();
    void printResult(HUSKYLENSResult result);
};
#endif