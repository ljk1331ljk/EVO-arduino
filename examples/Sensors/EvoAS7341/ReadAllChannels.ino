#include <Evo.h>
#include <sensors/EvoAS7341.h>

// Function prototypes
void testReadChannels();
void testSensorInit();
void testLEDFlicker();

// Global variables to avoid reinitialization
EVOX1 evo;
EvoAS7341 as(I2C1);
bool initialized = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Perform one-time initialization for the sensor
  evo.begin();
  if (!as.begin()) {
    Serial.println(F("AS7341 initialisation failed!"));
    while (1);
  }
  as.powerEnable(true);
  Serial.println(F("AS7341 initialised successfully."));

  as.setIntegration(50, 599, AS7341_GAIN_64X);
  Serial.println(F("AS7341 Integration Set."));

  Serial.print("ATIME: ");
  Serial.println(as.getATIME());
  Serial.print("ASTEP: ");
  Serial.println(as.getASTEP());
  Serial.print("Gain: ");
  Serial.println(as.getGain());
  Serial.print("TINT: ");
  Serial.print(as.getTINT());
  Serial.println("ms");

  as.enableLED(true);
  as.setLEDCurrent(10);

  evo.waitForBump();
}

void loop() {
  testReadChannels();
  // testSensorInit();
  // testLEDFlicker();
}

// Function to test reading and normalizing channels
void testReadChannels() {
  static uint16_t readings[12];
  static float normalized_readings[12];
  static const char* colours[] = { "Violet", "Indigo", "Blue", "Cyan", "CLR0", "NIR0", "Green", "Yellow", "Orange", "Red", "CLR", "NIR" };
  static const char* channels[] = { "F1:", "F2:", "F3:", "F4:", "F5:", "F6:", "F7:", "F8:", "F9:", "F10:", "F11:", "F12:" };
  char label[8];

  evo.clearDisplay();

  if (!as.readAllChannels(readings)) {
    Serial.println("Error reading all channels!");
    return;
  }

  for (int i = 0; i < 12; i++) {
    if (i < 6) {
      evo.writeToDisplay(channels[i], 0, i * 8); // Write channel label
      evo.writeToDisplay(readings[i], 24, i * 8); // Write channel value
    } else {
      evo.writeToDisplay(channels[i], 64, (i - 6) * 8); // Write channel label
      evo.writeToDisplay(readings[i], 88, (i - 6) * 8); // Write channel value
    }

    // Serial.print(colours[i]);
    // Serial.print(": ");
    // Serial.print(readings[i], 4);
    // Serial.print(" ");
  }
  // Serial.print("--- Normalized: ");

  as.normalizeChannels(readings, normalized_readings);

  for (int i = 0; i < 12; i++) {
    // Serial.print(colours[i]);
    // Serial.print(": ");
    Serial.print(normalized_readings[i], 3);
    Serial.print(" ");
  }
  Serial.println();

  evo.drawDisplay();
}

// Function to test LED and flicker detection
void testLEDFlicker() {
  static bool ledInitialized = false;

  if (!ledInitialized) {
    as.enableLED(true);
    as.setLEDCurrent(50);
    ledInitialized = true;
  }

  uint16_t flicker = as.detectFlickerHz();
  Serial.print("Flicker Frequency: ");
  Serial.println(flicker);

  delay(1000); // Add a delay to avoid spamming the output
}