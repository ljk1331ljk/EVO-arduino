#ifndef EVO_X1P_H
#define EVO_X1P_H
#include "ControllerDefinition.h"
#include "EvoControllerBase.h"
class EvoX1P : public EvoControllerBase {
public:
    static constexpr EvoControllerId ID = EvoControllerId::X1P;
    static constexpr const char *NAME = "Evo X1P";
    static constexpr bool HAS_RGB_LED = false;
    static constexpr bool HAS_DISPLAY = true;
    static constexpr bool HAS_BUZZER = true;
    static constexpr bool HAS_EV3_SENSOR_PORTS = false;
    static constexpr bool HAS_BATTERY_CHARGER = true;
    static constexpr bool HAS_I2C_MULTIPLEXER = true;
    static constexpr bool HAS_HC05 = false;
    static constexpr bool HAS_PWM_MULTIPLEXER = true;
    static constexpr bool HAS_BOOT_LED = true;
    static constexpr bool HAS_SHUTDOWN_PIN = true;
    static constexpr bool HAS_NSLEEP_PIN = true;
    static constexpr uint8_t MOTOR_COUNT = 4;
    static constexpr uint8_t SERVO_COUNT = 4;
    static constexpr uint8_t GPIO_COUNT = 4;
    static constexpr uint8_t BUTTON_COUNT = 3;
    static constexpr uint8_t I2C_CHANNEL_COUNT = 8;
    static constexpr uint8_t GPIO1A=5,GPIO1B=4,GPIO2A=7,GPIO2B=6;
    static constexpr uint8_t TACH41=42,TACH42=39,TACH31=41,TACH32=40,TACH21=38,TACH22=48,TACH11=47,TACH12=21;
    static constexpr uint8_t MOTOR11=12,MOTOR12=13,MOTOR21=15,MOTOR22=14,MOTOR31=0,MOTOR32=1,MOTOR41=2,MOTOR42=3;
    static constexpr uint8_t I2C1=0,I2C2=1,I2C3=2,I2C4=3,I2C5=7,I2C6=6,I2C7=4,I2C8=5;
    static constexpr uint8_t BUZZER_PIN=8,BUTTON_PIN_1=11,BUTTON_PIN_2=10,BUTTON_PIN_3=3;
    static constexpr uint8_t NSLEEP_PIN=46,BOOT_LED_PIN=45,SHUTDOWN_PIN=14;
    static constexpr uint8_t SDA0_PIN=1,SCL0_PIN=2,SDA1_PIN=12,SCL1_PIN=13;
    static constexpr uint8_t TCA9548A_ADDR=0x70,SSD1309_ADDR=0x3C,SSD1309_CHANNEL_NUMBER=I2C8,BATTERY_CHARGER_ADDRESS=0x6A,PCA9685PW_ADDRESS=0x40;
    EvoX1P(){ static_assert(SelectedEvoController::ID == EvoControllerId::X1P, "EvoX1P requires EVO_BOARD_X1P."); }
};
#endif
