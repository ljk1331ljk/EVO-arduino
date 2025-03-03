#ifndef X1PINS_H
#define X1PINS_H

#define V3_0

#ifdef V3_0

#define PIN_VERSION "V3.0"
// LEGO Sensor pins
#define S11 10
#define S12 9
#define S21 8
#define S22 3
#define S31 7
#define S32 6
#define S41 5
#define S42 4

#define GPIO1 10
#define GPIO2 9
#define GPIO3 8
#define GPIO4 3
#define GPIO5 7
#define GPIO6 6
#define GPIO7 5
#define GPIO8 4

// Motor pins
#define TACH41 42
#define TACH42 41
#define TACH31 40
#define TACH32 39
#define TACH21 38
#define TACH22 48
#define TACH11 47
#define TACH12 21
// Through PCA9685PW
#define MOTOR21 13
#define MOTOR22 12
#define MOTOR11 14
#define MOTOR12 15
#define MOTOR41 9
#define MOTOR42 8
#define MOTOR31 11
#define MOTOR32 10

#define BUZZER_PIN 11
#define BUTTON_PIN 14
#define PIXEL_PIN 14

// I2C
#define SDA0_PIN 1
#define SCL0_PIN 2

#define TCA9548A_ADDR (0x70)

#define SSD1309_ADDR (0x3C)
#define SSD1309_CHANNEL I2C8

#define SDA1_PIN 12
#define SCL1_PIN 13

#define BATTERY_CHARGER_ADDRESS (0x6A)
#define PCA9685PW_ADDRESS (0x40)

#else // V2.0

#define PIN_VERSION "V2.0"

#define S11 41
#define S12 42
#define S21 39
#define S22 40
#define S31 38
#define S32 48
#define S41 47
#define S42 21
// Motor pins
#define TACH41 4
#define TACH42 5
#define TACH31 6
#define TACH32 7
#define TACH21 15
#define TACH22 16
#define TACH11 8
#define TACH12 9
// Through PCA9685PW
#define MOTOR11 8
#define MOTOR12 9
#define MOTOR21 10
#define MOTOR22 11
#define MOTOR31 12
#define MOTOR32 13
#define MOTOR41 14
#define MOTOR42 15

#define BUZZER_PIN 14
#define BUTTON_PIN 10
#define PIXEL_PIN 10

// I2C
#define SDA0_PIN 1
#define SCL0_PIN 2

#define TCA9548A_ADDR (0x70)

#define SSD1309_ADDR (0x3C)
#define SSD1309_CHANNEL I2C8

#define SDA1_PIN 12
#define SCL1_PIN 13

#define BATTERY_CHARGER_ADDRESS (0x6A)
#define PCA9685PW_ADDRESS (0x40)

#endif

#endif