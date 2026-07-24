#ifndef EVO_X1E_H
#define EVO_X1E_H
#include "ControllerDefinition.h"
#include "EvoControllerBase.h"
class EvoX1E : public EvoControllerBase {
public:
    static constexpr EvoControllerId ID = EvoControllerId::X1E;
    static constexpr const char *NAME = "Evo X1E";
    static constexpr bool HAS_RGB_LED = true;
    static constexpr bool HAS_DISPLAY = true;
    static constexpr bool HAS_BUZZER = true;
    static constexpr bool HAS_EV3_SENSOR_PORTS = true;
    static constexpr bool HAS_BATTERY_CHARGER = true;
    static constexpr bool HAS_I2C_MULTIPLEXER = true;
    static constexpr bool HAS_HC05 = true;
    static constexpr bool HAS_PWM_MULTIPLEXER = true;
    static constexpr bool HAS_BOOT_LED = false;
    static constexpr bool HAS_SHUTDOWN_PIN = false;
    static constexpr bool HAS_NSLEEP_PIN = false;
    static constexpr uint8_t MOTOR_COUNT = 4;
    static constexpr uint8_t SERVO_COUNT = 8;
    static constexpr uint8_t GPIO_COUNT = 8;
    static constexpr uint8_t BUTTON_COUNT = 1;
    static constexpr uint8_t I2C_CHANNEL_COUNT = 8;
    static constexpr uint8_t S11=10,S12=9,S21=8,S22=3,S31=7,S32=6,S41=5,S42=4;
    static constexpr uint8_t GPIO1=10,GPIO2=9,GPIO3=8,GPIO4=3,GPIO5=7,GPIO6=6,GPIO7=5,GPIO8=4;
    static constexpr uint8_t HC05_PWR=45,HC05_RESET=46;
    static constexpr uint8_t TACH41=42,TACH42=41,TACH31=40,TACH32=39,TACH21=38,TACH22=48,TACH11=47,TACH12=21;
    static constexpr uint8_t MOTOR21=13,MOTOR22=12,MOTOR11=14,MOTOR12=15,MOTOR41=9,MOTOR42=8,MOTOR31=11,MOTOR32=10;
    static constexpr uint8_t BUZZER_PIN=11,BUTTON_PIN=14,PIXEL_PIN=14;
    static constexpr uint8_t SDA0_PIN=1,SCL0_PIN=2,SDA1_PIN=12,SCL1_PIN=13;
    static constexpr uint8_t TCA9548A_ADDR=0x70,SSD1309_ADDR=0x3C,SSD1309_CHANNEL_NUMBER=8,BATTERY_CHARGER_ADDRESS=0x6A,PCA9685PW_ADDRESS=0x40;
    EvoX1E(){ static_assert(SelectedEvoController::ID == EvoControllerId::X1E, "EvoX1E requires EVO_BOARD_X1E."); }
};
#endif
