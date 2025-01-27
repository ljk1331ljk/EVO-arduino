#include "EV3ColorSensor.h"

const static char *TAG = "EV3ColorSensor";

EV3ColorSensor::EV3ColorSensor(SensorPort port) : _EV3port(port)
{
    _port = port;
    _EV3port.setMessageHandler([this](uint8_t mode, uint8_t *message, int length)
                               { this->messageHandler(mode, message, length); });
}

bool EV3ColorSensor::begin()
{
    if (_EV3port.begin())
    {
        _mode = EV3ColorSensorMode::COL_REFLECT;
        return true;
    }
    return false;
}

void EV3ColorSensor::setMode(EV3ColorSensorMode mode)
{
    while (_mode != mode)
    {
        _EV3port.selectSensorMode(static_cast<uint8_t>(mode));
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void EV3ColorSensor::messageHandler(uint8_t mode, uint8_t *message, int length)
{
    _mode = (EV3ColorSensorMode)mode;
    switch (mode)
    {
    case 0:
    case 1:
    case 2:
        value = message[0];
        break;
    default:
        ESP_LOGE(TAG, "Currently not supported EV3 color sensor mode %d", mode);
    }
}

int EV3ColorSensor::getReflection()
{
    if (_mode != EV3ColorSensorMode::COL_REFLECT)
    {
        this->setMode(EV3ColorSensorMode::COL_REFLECT);
    }
    return value;
}
int EV3ColorSensor::getAmbient()
{
    if (_mode != EV3ColorSensorMode::COL_AMBIENT)
    {
        this->setMode(EV3ColorSensorMode::COL_AMBIENT);
    }
    return value;
}
int EV3ColorSensor::getColor()
{
    if (_mode != EV3ColorSensorMode::COL_COLOR)
    {
        this->setMode(EV3ColorSensorMode::COL_COLOR);
    }
    return value;
}

const char *toColor(int col)
{
    switch ((EV3ColorSensorColor)col)
    {
    case EV3ColorSensorColor::NONE:
        return "none";
        break;
    case EV3ColorSensorColor::COLOR_BLACK:
        return "black";
        break;
    case EV3ColorSensorColor::COLOR_BLUE:
        return "blue";
        break;
    case EV3ColorSensorColor::COLOR_GREEN:
        return "green";
        break;
    case EV3ColorSensorColor::COLOR_YELLOW:
        return "yellow";
        break;
    case EV3ColorSensorColor::COLOR_RED:
        return "red";
        break;
    case EV3ColorSensorColor::COLOR_WHITE:
        return "white";
        break;
    case EV3ColorSensorColor::COLOR_BROWN:
        return "brown";
        break;
    default:
        ESP_LOGE(TAG, "Unknown color %d", static_cast<uint8_t>(col));
        return "unknown";
    }
}
