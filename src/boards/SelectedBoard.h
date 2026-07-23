#ifndef EVO_SELECTED_BOARD_H
#define EVO_SELECTED_BOARD_H

/*
 * The Arduino Boards Manager package must set build.board to either:
 *
 *   EVO_X1E  -> Arduino defines ARDUINO_EVO_X1E
 *   EVO_X1P  -> Arduino defines ARDUINO_EVO_X1P
 */

#if defined(EVO_BOARD_X1E)

#include "BoardX1E.h"
using EvoBoard = BoardX1E;

#elif defined(EVO_BOARD_X1P)

#include "BoardX1P.h"
using EvoBoard = BoardX1P;

#else

#error "No EVO controller selected. Select Evo X1E or Evo X1P from Tools > Board."

#endif

/*
 * Compatibility macros for the current codebase.
 *
 * Existing drivers can continue using MOTOR11, TACH11, SDA0_PIN, etc.
 * New code should prefer EvoBoard::MOTOR11, EvoBoard::TACH11, and so on.
 */

#define S11 EvoBoard::S11
#define S12 EvoBoard::S12
#define S21 EvoBoard::S21
#define S22 EvoBoard::S22
#define S31 EvoBoard::S31
#define S32 EvoBoard::S32
#define S41 EvoBoard::S41
#define S42 EvoBoard::S42

#define GPIO1 EvoBoard::GPIO1
#define GPIO2 EvoBoard::GPIO2
#define GPIO3 EvoBoard::GPIO3
#define GPIO4 EvoBoard::GPIO4
#define GPIO5 EvoBoard::GPIO5
#define GPIO6 EvoBoard::GPIO6
#define GPIO7 EvoBoard::GPIO7
#define GPIO8 EvoBoard::GPIO8

#define HC05_PWR EvoBoard::HC05_PWR
#define HC05_RESET EvoBoard::HC05_RESET

#define TACH11 EvoBoard::TACH11
#define TACH12 EvoBoard::TACH12
#define TACH21 EvoBoard::TACH21
#define TACH22 EvoBoard::TACH22
#define TACH31 EvoBoard::TACH31
#define TACH32 EvoBoard::TACH32
#define TACH41 EvoBoard::TACH41
#define TACH42 EvoBoard::TACH42

#define MOTOR11 EvoBoard::MOTOR11
#define MOTOR12 EvoBoard::MOTOR12
#define MOTOR21 EvoBoard::MOTOR21
#define MOTOR22 EvoBoard::MOTOR22
#define MOTOR31 EvoBoard::MOTOR31
#define MOTOR32 EvoBoard::MOTOR32
#define MOTOR41 EvoBoard::MOTOR41
#define MOTOR42 EvoBoard::MOTOR42

#define BUZZER_PIN EvoBoard::BUZZER_PIN
#define BUTTON_PIN EvoBoard::BUTTON_PIN
#define PIXEL_PIN EvoBoard::PIXEL_PIN

#define SDA0_PIN EvoBoard::SDA0_PIN
#define SCL0_PIN EvoBoard::SCL0_PIN
#define SDA1_PIN EvoBoard::SDA1_PIN
#define SCL1_PIN EvoBoard::SCL1_PIN

#define TCA9548A_ADDR EvoBoard::TCA9548A_ADDR
#define SSD1309_ADDR EvoBoard::SSD1309_ADDR
#define BATTERY_CHARGER_ADDRESS EvoBoard::BATTERY_CHARGER_ADDRESS
#define PCA9685PW_ADDRESS EvoBoard::PCA9685PW_ADDRESS

/*
 * I2C1 ... I2C8 are existing I2CChannel enum values, so retain the
 * current symbolic channel name rather than converting it to an integer.
 */
#define SSD1309_CHANNEL I2C8

#endif
