#ifndef EVO_BOARD_X1E_H
#define EVO_BOARD_X1E_H

#include "BoardDefinition.h"

struct BoardX1E
{
    static constexpr EvoBoardId ID = EvoBoardId::X1E;
    static constexpr const char *NAME = "Evo X1E";

    static constexpr uint8_t MOTOR_COUNT = 4;
    static constexpr uint8_t SERVO_COUNT = 8;
    static constexpr uint8_t GPIO_COUNT = 8;
    static constexpr uint8_t I2C_CHANNEL_COUNT = 8;

    // LEGO sensor / GPIO pins
    static constexpr uint8_t S11 = 10;
    static constexpr uint8_t S12 = 9;
    static constexpr uint8_t S21 = 8;
    static constexpr uint8_t S22 = 3;
    static constexpr uint8_t S31 = 7;
    static constexpr uint8_t S32 = 6;
    static constexpr uint8_t S41 = 5;
    static constexpr uint8_t S42 = 4;

    static constexpr uint8_t GPIO1 = 10;
    static constexpr uint8_t GPIO2 = 9;
    static constexpr uint8_t GPIO3 = 8;
    static constexpr uint8_t GPIO4 = 3;
    static constexpr uint8_t GPIO5 = 7;
    static constexpr uint8_t GPIO6 = 6;
    static constexpr uint8_t GPIO7 = 5;
    static constexpr uint8_t GPIO8 = 4;

    // HC-05
    static constexpr uint8_t HC05_PWR = 45;
    static constexpr uint8_t HC05_RESET = 46;

    // Encoder pins
    static constexpr uint8_t TACH41 = 42;
    static constexpr uint8_t TACH42 = 41;
    static constexpr uint8_t TACH31 = 40;
    static constexpr uint8_t TACH32 = 39;
    static constexpr uint8_t TACH21 = 38;
    static constexpr uint8_t TACH22 = 48;
    static constexpr uint8_t TACH11 = 47;
    static constexpr uint8_t TACH12 = 21;

    // PCA9685 motor channels
    static constexpr uint8_t MOTOR21 = 13;
    static constexpr uint8_t MOTOR22 = 12;
    static constexpr uint8_t MOTOR11 = 14;
    static constexpr uint8_t MOTOR12 = 15;
    static constexpr uint8_t MOTOR41 = 9;
    static constexpr uint8_t MOTOR42 = 8;
    static constexpr uint8_t MOTOR31 = 11;
    static constexpr uint8_t MOTOR32 = 10;

    static constexpr uint8_t BUZZER_PIN = 11;
    static constexpr uint8_t BUTTON_PIN = 14;
    static constexpr uint8_t PIXEL_PIN = 14;

    // I2C
    static constexpr uint8_t SDA0_PIN = 1;
    static constexpr uint8_t SCL0_PIN = 2;
    static constexpr uint8_t SDA1_PIN = 12;
    static constexpr uint8_t SCL1_PIN = 13;

    static constexpr uint8_t TCA9548A_ADDR = 0x70;
    static constexpr uint8_t SSD1309_ADDR = 0x3C;
    static constexpr uint8_t SSD1309_CHANNEL_NUMBER = 8;
    static constexpr uint8_t BATTERY_CHARGER_ADDRESS = 0x6A;
    static constexpr uint8_t PCA9685PW_ADDRESS = 0x40;
};

#endif
