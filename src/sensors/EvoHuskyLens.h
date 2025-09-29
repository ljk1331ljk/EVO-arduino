#ifndef EVO_HUSKY_LENS_H
#define EVO_HUSKY_LENS_H

#include "../helper/EvoI2CDevice.h"
#include "../helper/HuskyLens/HUSKYLENS.h"

/**
 * @class EvoHuskyLens
 * @brief A class for interfacing with the HuskyLens AI vision sensor using I2C.
 */
class EvoHuskyLens
{
private:
    HUSKYLENS huskylens;
    I2CChannel _channel;
    I2CDevice &i2CDevice = I2CDevice::getInstance();
    protocolAlgorithm _algorithmType = ALGORITHM_COLOR_RECOGNITION;

public:
    /**
     * @brief Constructor for EvoHuskyLens.
     * @param channel The I2C channel used to communicate with the HuskyLens.
     */
    EvoHuskyLens(I2CChannel channel)
    {
        _channel = channel;
    }

    /**
     * @brief Initializes the HuskyLens sensor.
     * This method sets up the HuskyLens for communication over I2C.
     * It must be called before any other methods to ensure the HuskyLens is ready for use.
     * Default mode is set to ALGORITHM_COLOR_RECOGNITION.
     * @return True if the HuskyLens was successfully initialized, false otherwise.
     */
    bool begin();
    /**
     * @brief Sets the operating mode (algorithm) of the HuskyLens.
     *
     * The HuskyLens supports multiple AI algorithms for different types of object recognition and tracking:
     * - `ALGORITHM_FACE_RECOGNITION`: Recognizes and tracks human faces.
     * - `ALGORITHM_OBJECT_TRACKING`: Tracks user-defined objects.
     * - `ALGORITHM_OBJECT_RECOGNITION`: Recognizes multiple learned objects.
     * - `ALGORITHM_LINE_TRACKING`: Detects and follows lines.
     * - `ALGORITHM_COLOR_RECOGNITION`: Recognizes specific colors.
     * - `ALGORITHM_TAG_RECOGNITION`: Recognizes and tracks AprilTags.
     * @param algorithmType The algorithm mode to set.
     */
    void setMode(protocolAlgorithm algorithmType);

    /**
     * @brief Gets the current operating mode of the HuskyLens.
     * @return The current algorithm type.
     */
    protocolAlgorithm getMode();

    /**
     * @brief Gets the current operating mode of the HuskyLens.
     * @return A string representation of the current mode.
     * - ALGORITHM_FACE_RECOGNITION : "FACE REC"
     * - ALGORITHM_OBJECT_TRACKING : "OBJ TRK"
     * - ALGORITHM_OBJECT_RECOGNITION : "OBJ REC"
     * - ALGORITHM_LINE_TRACKING : "LINE TRK"
     * - ALGORITHM_COLOR_RECOGNITION : "COLOR REC"
     * - ALGORITHM_TAG_RECOGNITION : "TAG REC"
     * - Returns "UNKNOWN" if the mode is not recognized.
     */
    String getModeString();

    /**
     * @brief Requests detected blocks from the HuskyLens.
     * @param result Reference to a HUSKYLENSResult structure to store the results.
     * @param ID (Optional) The specific ID of the object to track (default: 0 for all).
     * @return True if blocks were successfully retrieved, false otherwise.
     */
    bool requestBlocks(HUSKYLENSResult &result, int16_t ID = 0);

    /**
     * @brief Requests detected arrows from the HuskyLens.
     * @param result Reference to a HUSKYLENSResult structure to store the results.
     * @param ID (Optional) The specific ID of the arrow to track (default: 0 for all).
     * @return True if arrows were successfully retrieved, false otherwise.
     */
    bool requestArrows(HUSKYLENSResult &result, int16_t ID = 0);

    /**
     * @brief Writes a string to the HuskyLens display.
     * @param text The text to display.
     * @param x The x-coordinate position.
     * @param y The y-coordinate position.
     */
    void writeString(String text, uint16_t x, uint8_t y);

    /**
     * @brief Clears the HuskyLens display screen.
     */
    void clearScreen();

    /**
     * @brief Prints the result of an object or arrow detected by HuskyLens.
     * @param result The detection result to print.
     */
    void printResult(HUSKYLENSResult result);
};
#endif
