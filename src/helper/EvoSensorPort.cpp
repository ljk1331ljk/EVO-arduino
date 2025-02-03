#include "EvoSensorPort.h"

static const char *TAG = "EvoSensorPort";

EvoSensorPort::EvoSensorPort(SensorPort port) : _port(port)
{
    // _port = port;
    switch (_port)
    {
    case S1:
        _rxPin = S12;
        _txPin = S11;
        break;
    case S2:
        _rxPin = S22;
        _txPin = S21;
        break;
    case S3:
        _rxPin = S32;
        _txPin = S31;
        break;
    case S4:
        _rxPin = S42;
        _txPin = S41;
        break;
    }
    this->_serialMutex = xSemaphoreCreateMutex();
}

void EvoSensorPort::setBaudrate(uint8_t baud)
{
    _sw.begin(baud, SWSERIAL_8N1, _txPin, _rxPin);
}

bool EvoSensorPort::begin(int retries)
{
    stop();
    this->retries = retries;

    xTaskCreatePinnedToCore(
        sensorThread,
        "EV3Sensor",
        50000,
        this,
        1,
        &_sensorHandle, // Task handle
        1);
    int timeout = 10000;
    int timenow = millis();
    while (millis() - timenow < timeout)
    {
        if (_portInitialised == true)
        {
            return true;
        }
        vTaskDelay(1);
    }
    Serial.println("begin timeout");
    return false;
}

void EvoSensorPort::sensorThread(void *parameter)
{
    EvoSensorPort *sensor = (EvoSensorPort *)parameter;
    vTaskDelay(3000);
    while (true)
    {
        if (!sensor->_portInitialised)
        {
            ESP_LOGV(TAG, "sensor started");
            sensor->initSensor(sensor);
        }
        else
        {
            sensor->sensorCommThread();
        }
        vTaskDelay(1);
    }
}

void EvoSensorPort::initSensor(EvoSensorPort *sensor)
{
    byte message = 0;
    xSemaphoreTake(_serialMutex, portMAX_DELAY);
    _sw.begin(2400, SWSERIAL_8N1, this->_txPin, this->_rxPin);
    ESP_LOGV(TAG, "Waiting from the first TYPE message from the EV3 sensor. %d retries left", retries);

    while (message != TYPE)
    {
        message = this->readNextAvailableByte();
        vTaskDelay(1);
    }

    if (this->parseType(message, &_config))
    {
        // Wait for the next message
        bool waitingForConfig = true;
        while (waitingForConfig)
        {
            // Clear buffer
            std::fill(_buffer, _buffer + BUFFER_SIZE, 0);
            message = this->readNextAvailableByte();
            if (message == MODES)
            {
                if (!this->parseModeCount(message, &_config))
                {
                    ESP_LOGE(TAG, "Failed to parse mode count -> restart (%d retries left)", retries - 1);
                    xSemaphoreGive(_serialMutex);
                    vTaskDelay(TIME_BEFORE_RESTART);
                    retries--;
                    return;
                }
                _config.infos = new EV3SensorInfo[_config.modes];
            }
            else if (message == SPEED)
            {
                if (!this->parseSpeed(message, &_config))
                {
                    ESP_LOGE(TAG, "Failed to parse sensor uart speed -> restart (%d retries left)", retries - 1);
                    xSemaphoreGive(_serialMutex);
                    vTaskDelay(TIME_BEFORE_RESTART);
                    retries--;
                    return;
                }
            }
            else if (message & 0b10000000)
            {
                // Found info message
                byte modeNumber = message & 0b111;
                EV3SensorInfo info = _config.infos[modeNumber];
                if (!this->parseInfoMessage(message, &info))
                {
                    ESP_LOGE(TAG, "Failed to parse sensor info message -> restart (%d retries left)", retries - 1);
                    xSemaphoreGive(_serialMutex);
                    vTaskDelay(TIME_BEFORE_RESTART);
                    retries--;
                    return;
                }
            }
            else if (message == ACK)
            {
                waitingForConfig = false;
                ESP_LOGV(TAG, "-----------------------------------------------------");
                ESP_LOGV(TAG, "Fully received sensor config");

                ESP_LOGV(TAG, "Reply sensor config with ACK");
                _sw.write(ACK);
                _sw.flush();

                ESP_LOGV(TAG, "Set new UART speed to %d baud", this->_config.speed);
                _sw.begin(this->_config.speed, SWSERIAL_8N1, this->_txPin, this->_rxPin);
                xSemaphoreGive(_serialMutex);
                // _onSuccess(this);

                ESP_LOGV(TAG, "Initalization phase finished - switching to communication phase");
                this->_portInitialised = true;
            }
            vTaskDelay(1);
        }
    }
    else
    {
        xSemaphoreGive(_serialMutex);
        ESP_LOGE(TAG, "Failed communicate with sensor, retrying in %d ", TIME_BEFORE_RESTART);
        vTaskDelay(TIME_BEFORE_RESTART);
    }
}

void EvoSensorPort::sensorCommThread()
{
    timeout_cnt = millis() + TIMEOUT;

    while (this->_portInitialised)
    {
        xSemaphoreTake(_serialMutex, portMAX_DELAY);
        if (_sw.available() > 0)
        {
            // Clear buffer
            std::fill(_buffer, _buffer + BUFFER_SIZE, 0);
            uint8_t message = _sw.read();
            if (message & 0b11000000) // data message
            {
                uint8_t mode = message & 0b111;
                uint8_t msgLenght = 1 << ((message & 0b00111000) >> 3);
                ESP_LOGV(TAG, "received message mode %d message length %d", mode, msgLenght);
                _buffer[0] = message;
                _sw.readBytes(_buffer + 1, msgLenght + 1);

                if (calculateChecksum(_buffer, msgLenght + 1) == _buffer[msgLenght + 1])
                {
                    // send data out
                    if (this->_onMessage)
                    {
                        _onMessage(mode, _buffer + 1, msgLenght);
                    }
                    timeout_cnt = millis() + TIMEOUT;
                }
                else
                {
                    ESP_LOGV(TAG, "Got data message from sensor for mode %d with length %d but wrong checksum.", mode, msgLenght);
                }
            }
        }
        xSemaphoreGive(_serialMutex);

        auto current_timestamp = millis();
        auto delta_time = current_timestamp - this->lastNACKSended;
        if (timeout_cnt <= current_timestamp)
        {
            ESP_LOGD(TAG, "EV3 Sensor port: Timeout occured. No messages for %d ms. Restart ...", TIMEOUT);
            this->_portInitialised = false;
            break;
        }

        if (delta_time > 50)
        {
            xSemaphoreTake(_serialMutex, portMAX_DELAY);
            _sw.write(NACK);
            xSemaphoreGive(_serialMutex);
            this->lastNACKSended = current_timestamp;
        }
        vTaskDelay(1);
    }
}

uint8_t EvoSensorPort::calculateChecksum(uint8_t data[], int length)
{
    uint8_t result = 0xff;
    for (int i = 0; i < length; i++)
    {
        result ^= data[i];
    }
    return result;
}

char *EvoSensorPort::makeStringFromPayload(uint8_t data[], int maxlength)
{

    int actualLength = strlen((char *)data);
    actualLength = actualLength > maxlength ? maxlength : actualLength;
    char *result = new char[actualLength + 1];

    for (int i = 0; i < actualLength; i++)
    {
        result[i] = data[i];
    }
    result[actualLength] = 0;

    return result;
}

/**
 * Utlity method the read the next available byte from the connection.
 */
byte EvoSensorPort::readNextAvailableByte()
{
    byte message;
    while (true)
    {
        if (_sw.available() > 0)
        {
            message = _sw.read();
            break;
        }
        vTaskDelay(1);
    }
    return message;
}

bool EvoSensorPort::parseSpeed(byte header, EV3SensorConfig *config)
{
    _buffer[0] = header;

    _sw.readBytes(_buffer + 1, 5);
    if (calculateChecksum(_buffer, 5) == _buffer[5])
    {
        config->speed = (_buffer[4] << 24) + (_buffer[3] << 16) + (_buffer[2] << 8) + (_buffer[1] << 0);
        ESP_LOGV(TAG, "Found EV3 sensor to expect %d baud as communication baudrate", config->speed);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for SPEED system message.");
        return false;
    }
}

bool EvoSensorPort::parseModeCount(byte header, EV3SensorConfig *config)
{
    _buffer[0] = header;
    _sw.readBytes(_buffer + 1, 3);
    if (calculateChecksum(_buffer, 3) == _buffer[3])
    {
        config->modes = _buffer[1] + 1;
        config->modes_shown = _buffer[2] + 1;
        ESP_LOGV(TAG, "Found EV3 sensor with %d modes and %d modes presented.", config->modes, config->modes_shown);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for MODES system message.");
        return false;
    }
}

bool EvoSensorPort::parseType(byte message, EV3SensorConfig *config)
{
    _buffer[0] = message;

    _sw.readBytes(_buffer + 1, 2);
    if (calculateChecksum(_buffer, 2) == _buffer[2])
    {
        config->type = _buffer[1];
        ESP_LOGD(TAG, "Found EV3 sensor: %d.", config->type);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for TYPE system message.");
        return false;
    }
}

float EvoSensorPort::makeFloatFromPayload(uint8_t data[])
{
    uint32_t flt = (float)(data[3] << 24) + (data[2] << 16) + (data[1] << 8) + (data[0] << 0);
    float result = *reinterpret_cast<float *>(&flt);
    return result;
}

bool EvoSensorPort::parseInfoMessage(byte message, EV3SensorInfo *info)
{
    _buffer[0] = message;
    _sw.readBytes(_buffer + 1, 1);

    byte infoType = _buffer[1];

    if (infoType == 0)
    {
        ESP_LOGV(TAG, "-----------------------------------------------------");
    }

    switch (infoType)
    {
    case 0:
        return parseModeNameMessage(_buffer, info);
        break;
    case 1:
    case 2:
    case 3:
        return parseModeRangeMessage(_buffer, info);
        break;

    case 0x80:
        return parseFormatMessage(_buffer, info);
        break;
    case 4:
        return parseSymbolNameMessage(_buffer, info);
        break;
    default:
        return parseUnknownMessage(_buffer);
    }
}

bool EvoSensorPort::parseUnknownMessage(byte *header)
{
    _buffer[0] = header[0];
    _buffer[1] = header[1];

    // Read bytes until the checksum fits
    uint8_t msgLenght = 1 << ((header[0] & 0b00111000) >> 3); // 2^LLL;
    uint8_t mode = _buffer[0] & 0b111;
    uint8_t msglength = 2;
    uint8_t checksum = 0;

    for (;;)
    {
        checksum = _buffer[msglength - 1];
        if (calculateChecksum(_buffer, msglength - 1) == checksum)
        {
            // Message found !!!
            ESP_LOGD(TAG, "Unknown message %x (mode = %d, length = %d) for sensor mode %d", _buffer[0], mode, msgLenght, _buffer[1]);
            break;
        }
        else
        {
            // fetch next byte
            _sw.readBytes(_buffer + msglength, 1);
            msglength++;
        }
    }
    return true;
}

bool EvoSensorPort::parseSymbolNameMessage(byte *header, EV3SensorInfo *info)
{
    uint8_t msgLenght = 1 << ((header[0] & 0b00111000) >> 3); // 2^LLL;

    // Copy header to payload to simplify checksum calculation
    _buffer[0] = header[0];
    _buffer[1] = header[1];

    // Read the message string
    _sw.readBytes(_buffer + 2, msgLenght + 1); // Msg + checksum

    if (calculateChecksum(_buffer, msgLenght + 2) == _buffer[msgLenght + 2])
    {
        info->mode = _buffer[0] & 0b111;
        // Check actual name length
        info->siSymbol = makeStringFromPayload(_buffer + 2, msgLenght);
        ESP_LOGV(TAG, "Found symbol '%s' for sensor mode %d", info->siSymbol, info->mode);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for INFO system message 4.");
        return false;
    }
}

bool EvoSensorPort::parseModeNameMessage(byte *header, EV3SensorInfo *info)
{
    uint8_t msgLenght = 1 << ((header[0] & 0b00111000) >> 3); // 2^LLL;

    // Copy header to payload to simplify checksum calculation
    _buffer[0] = header[0];
    _buffer[1] = header[1];

    // Read the message string
    _sw.readBytes(_buffer + 2, msgLenght + 1); // Msg + checksum

    if (calculateChecksum(_buffer, msgLenght + 2) == _buffer[msgLenght + 2])
    {
        info->mode = _buffer[0] & 0b111;
        // Check actual name length
        info->name = makeStringFromPayload(_buffer + 2, msgLenght);
        ESP_LOGV(TAG, "Found name '%s' for sensor mode %d", info->name, info->mode);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for INFO system message 0.");
        return false;
    }
}

bool EvoSensorPort::parseFormatMessage(byte *header, EV3SensorInfo *info)
{
    _buffer[0] = header[0];
    _buffer[1] = header[1];
    _sw.readBytes(_buffer + 2, 5);

    if (calculateChecksum(_buffer, 6) == _buffer[6])
    {
        info->numberOfItems = _buffer[2];
        info->dataTypeOfItem = static_cast<EV3Datatype>(_buffer[3]);
        info->numberOfDigits = _buffer[4];
        info->numberOfDecimals = _buffer[5];
        info->mode = _buffer[0] & 0b111;

        ESP_LOGV(TAG, "Number of items per message %d of type %d with %d digits and with %d decimals for sensor mode %d", info->numberOfItems, static_cast<uint8_t>(info->dataTypeOfItem), info->numberOfDigits, info->numberOfDecimals, info->mode);
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for INFO system message 0x80.");
        return false;
    }
}

bool EvoSensorPort::parseModeRangeMessage(byte *header, EV3SensorInfo *info)
{
    _buffer[0] = header[0];
    _buffer[1] = header[1];
    _sw.readBytes(_buffer + 2, 11 - 2);
    byte infoType = _buffer[1];

    if (calculateChecksum(_buffer, 10) == _buffer[10])
    {
        info->mode = _buffer[0] & 0b111;
        float lowest = makeFloatFromPayload(_buffer + 2);
        float highest = makeFloatFromPayload(_buffer + 2 + 4);

        switch (infoType)
        {
        case 1:
            info->rawLowest = lowest;
            info->rawHighest = highest;
            ESP_LOGV(TAG, "RAW value between %f and %f for sensor mode %d", info->rawLowest, info->rawHighest, info->mode);
            break;
        case 2:
            info->pctLowest = lowest;
            info->pctHighest = highest;
            ESP_LOGV(TAG, "PCT value between %f and %f for sensor mode %d", info->pctLowest, info->pctHighest, info->mode);
            break;
        case 3:
            info->siLowest = lowest;
            info->siHighest = highest;
            ESP_LOGV(TAG, "SI value between %f and %f for sensor mode %d", info->siLowest, info->siHighest, info->mode);
            break;
        default:
            ESP_LOGD(TAG, "Unexpected info type %d for sensor mode %d", infoType, info->mode);
            return false;
        }
        return true;
    }
    else
    {
        ESP_LOGD(TAG, "Wrong checksum for INFO system message %d.", infoType);
        return false;
    }
}

bool EvoSensorPort::selectSensorMode(uint8_t mode)
{
    ESP_LOGD(TAG, "Setting sensor to mode %d", mode);

    _buffer[0] = SELECT;
    _buffer[1] = mode;
    _buffer[2] = this->calculateChecksum(_buffer, 2);
    xSemaphoreTake(_serialMutex, portMAX_DELAY);
    _sw.write(_buffer, 3);
    _sw.flush();
    xSemaphoreGive(_serialMutex);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    return true;
}

void EvoSensorPort::stop()
{
    ESP_LOGD(TAG, "Stopping sensor");
    if (_sensorHandle)
    {
        vTaskDelete(_sensorHandle);
        _sensorHandle = nullptr;
    }
}

/**
 * Utility method to get get EV3SensorInfo for a mode
 */
EV3SensorInfo *EvoSensorPort::getInfoForMode(uint8_t mode)
{
    if (getCurrentConfig())
    {
        auto config = getCurrentConfig();
        for (int i = 0; i < config->modes; i++)
        {
            if (config->infos[i].mode == mode)
            {
                return &config->infos[i];
            }
        }
    }
    return nullptr;
}
