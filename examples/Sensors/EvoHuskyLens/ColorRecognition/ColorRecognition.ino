#include <Evo.h>

EVOX1 evo;
EvoHuskyLens hl(I2C1);
HUSKYLENSResult result;

void setup()
{
  evo.begin();
  evo.writeLineToDisplay("HuskyLens", 0, true, true);
  hl.begin();
  hl.setMode(ALGORITHM_COLOR_RECOGNITION);
  /*
    The HuskyLens supports multiple AI algorithms for different types of object recognition and tracking:
    ALGORITHM_FACE_RECOGNITION      // Recognizes and tracks human faces.
    ALGORITHM_OBJECT_TRACKING       // Tracks user-defined objects.
    ALGORITHM_OBJECT_RECOGNITION    // Recognizes multiple learned objects.
    ALGORITHM_LINE_TRACKING         // Detects and follows lines.
    ALGORITHM_COLOR_RECOGNITION     // Recognizes specific colors.
    ALGORITHM_TAG_RECOGNITION       // Recognizes and tracks AprilTags.
    ALGORITHM_OBJECT_CLASSIFICATION // Classifies objects based on learned features.
  */
  hl.writeString("Color Recognition", 0, 0);

  evo.waitForBump();

  hl.clearScreen();
}

void loop()
{
  if (hl.requestBlocks(result))
  {
    hl.printResult(result);
    evo.clearDisplay();
    evo.writeLineToDisplay("HuskyLens", 0);
    evo.writeToDisplay("ID:", 0, 16);
    evo.writeToDisplay(result.ID, 40, 16);
    evo.writeToDisplay("Pos(x,y):", 0, 24);
    evo.writeToDisplay(result.xCenter, 60, 24);
    evo.writeToDisplay(result.yCenter, 90, 24);
    evo.writeToDisplay("Height:", 0, 32);
    evo.writeToDisplay(result.height, 60, 32);
    evo.writeToDisplay("Width:", 0, 40);
    evo.writeToDisplay(result.width, 60, 40);
    evo.drawDisplay();
  }
}
