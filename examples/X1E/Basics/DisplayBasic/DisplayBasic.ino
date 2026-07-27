#include <Evo.h>

EvoX1E evo;

void waitForNextPage()
{
  evo.writeLineToDisplay("Press button", 7, false, true);
  evo.waitForBump(1, 150);
}

void showFontSizes()
{
  const uint8_t fontSizes[] = {4, 5, 6, 7, 8, 9, 10};

  for (uint8_t size : fontSizes)
  {
    evo.clearDisplay();
    evo.setFontSize(size);
    evo.writeToDisplay("Font size", 0, 0);
    evo.writeToDisplay(size, 60, 0, false, true);
    delay(500);
  }
}

void showTextOverloads()
{
  evo.setFontSize(8);
  evo.clearDisplay();

  // const char*, int, and double coordinate-based overloads.
  evo.writeToDisplay("Text overloads", 0, 0);
  evo.writeToDisplay(12345, 0, 14);
  evo.writeToDisplay(3.14159, 0, 28);

  // const char*, int, and double line-based overloads.
  evo.writeLineToDisplay("Line text", 4);
  evo.writeLineToDisplay(6789, 5);
  evo.writeLineToDisplay(2.71828, 6, false, true);
  waitForNextPage();

  // Exercise the clear and immediate-draw options together.
  evo.writeToDisplay("clear + draw", 0, 0, true, true);
  delay(700);
  evo.writeLineToDisplay("line clear", 1, true, true);
  delay(700);
}

void showDrawingFunctions()
{
  evo.clearDisplay();

  evo.drawPixel(2, 2);
  evo.drawLine(0, 10, 127, 10);
  evo.drawRect(2, 14, 24, 18);
  evo.drawRect(30, 14, 24, 18, true);
  evo.drawCircle(70, 23, 10);
  evo.drawCircle(96, 23, 10, true);
  evo.drawTriangle(108, 32, 126, 32, 117, 14, false, true);
  waitForNextPage();

  // Exercise clear and immediate draw on each drawing primitive.
  evo.drawPixel(64, 32, true, true);
  delay(300);
  evo.drawLine(0, 0, 127, 63, true, true);
  delay(300);
  evo.drawRect(20, 12, 88, 40, false, true, true);
  delay(300);
  evo.drawCircle(64, 32, 24, false, true, true);
  delay(300);
  evo.drawTriangle(64, 4, 8, 58, 120, 58, true, true);
  delay(700);
}

void showOrientation()
{
  evo.clearDisplay();
  evo.flipDisplayOrientation(true);
  evo.writeToDisplay("Flipped", 0, 0, false, true);
  delay(800);

  evo.flipDisplayOrientation(false);
  evo.writeToDisplay("Normal", 0, 0, true, true);
  delay(800);
}

void setup()
{
  evo.begin();
  showFontSizes();
  showTextOverloads();
  showDrawingFunctions();
  showOrientation();
  evo.clearDisplay();
  evo.drawDisplay();
}

void loop()
{
}
