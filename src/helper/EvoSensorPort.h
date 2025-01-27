#ifndef EVO_SENSOR_PORT_H
#define EVO_SENSOR_PORT_H

#include <stdint.h>
#include <Arduino.h>
#include <functional>
#include <SoftwareSerial.h>
#include "X1pins.h"

enum SensorPort
{
    S1,
    S2,
    S3,
    S4
};

/**
 * Supported data types for messages from the sensor to the host.
 */
enum struct EV3Datatype : uint8_t
{
    INT8 = 0,
    INT16 = 1,
    INT32 = 2,
    FLOAT32 = 3
};

/**
 * Describes a single mode of a EV3 sensor.
 */
struct EV3SensorInfo
{
    byte mode;
    char *name = nullptr;
    float rawLowest = 0.0f;
    float rawHighest = 0.0f;
    float pctLowest = 0.0f;
    float pctHighest = 0.0f;
    float siLowest = 0.0f;
    float siHighest = 0.0f;
    char *siSymbol = nullptr;

    uint8_t numberOfItems = 0;
    EV3Datatype dataTypeOfItem = EV3Datatype::INT8;
    uint8_t numberOfDigits = 0;
    uint8_t numberOfDecimals = 0;
};

/**
 * Describes the modes of a EV3 sensor and the format of its messages.
 */
struct EV3SensorConfig
{
    uint8_t type;
    uint8_t modes = 0;
    uint8_t modes_shown = 0;
    uint32_t speed;

    EV3SensorInfo *infos;
};

/**
 * Sensor port of single EV3 sensor.
 * @see https://sourceforge.net/p/lejos/wiki/UART%20Sensor%20Protocol/
 */
class EvoSensorPort
{
public:
    bool _portInitialised = false;
    EvoSensorPort(SensorPort port);

    /**
     * Returns the sensor configuration found during the first phase of the EV3 protocol.
     */
    EV3SensorConfig *getCurrentConfig()
    {
        return &_config;
    }

    /**
     * Sets the message handler
     */
    void setMessageHandler(std::function<void(uint8_t, uint8_t *, int length)> onMessage)
    {
        this->_onMessage = onMessage;
    }

    /**
     *  Stops the EV3 Sensor communication and the corresponding task.
     */
    void stop();

    /**
     * Selects the working mode of the sensor
     */
    bool selectSensorMode(uint8_t mode);

    /**
     * Utility method to get get EV3SensorInfo for a mode
     */
    EV3SensorInfo *getInfoForMode(uint8_t mode);

    /**
     * Makes a float from a sensor payload
     */
    float makeFloatFromPayload(uint8_t data[]);

    /**
     * Starts the EV3 sensor communication protocol.
     * First reads the sensor configuration and calls the onSuccess callback afterwards. Then keeps the connection online by sending the sensor NACK regularly.
     * The method performs all commuincation in its own FreeRTOS task, there it returns immediately.
     */
    bool begin(int retries = 9);

private:
    SoftwareSerial _sw;
    uint8_t _txPin, _rxPin;
    SensorPort _port;
    EV3SensorConfig _config;

    std::function<void(uint8_t, uint8_t *, int length)> _onMessage;

    /**
     *  Callback called after sucessful connection with the sensor
     */
    std::function<void(EvoSensorPort *)> _onSuccess;

    /**
     * Number of retries left to connect to sensor.
     */
    int retries = 9;

    TaskHandle_t _sensorHandle;

    /**
     * Time in ms to wait for messages from the sensor before restarting the protocol
     */
    const static unsigned int TIMEOUT = 2000;

    int timeout_cnt = TIMEOUT;

    /**
     * Timestamp of the last NACK sended to sensor.
     */
    unsigned long lastNACKSended = 0;

    /**
     * Use one single buffer for all communication to avoid heap fragrmentation.
     */
    constexpr static size_t BUFFER_SIZE = 1 + 32 + 1;
    uint8_t _buffer[BUFFER_SIZE];

    const static uint8_t SYNC = 0b00000000;
    const static uint8_t NACK = 0b00000010;
    const static uint8_t ACK = 0b00000100;
    const static uint8_t TYPE = 0b01000000;
    const static uint8_t MODES = 0b01001001;
    const static uint8_t SPEED = 0b01010010;
    const static uint8_t SELECT = 0b01000011;

    const static uint8_t TYPE_COLOR_SENSOR = 29;
    const static uint8_t TYPE_IR_SENSOR = 33;

    const static TickType_t TIME_BEFORE_RESTART = 200 / portTICK_PERIOD_MS;

    // Prevent simultanious access quadrature encoder
    SemaphoreHandle_t _serialMutex;

    /**
     * Calculates the checksum
     */
    uint8_t calculateChecksum(uint8_t data[], int length);

    /**
     * Makes a string from a sensor payload. Since the payload is padded with zeros, the method tries first to determine the true size of the string.
     */
    char *makeStringFromPayload(uint8_t data[], int maxlength);

    void sensorCommThread();

    /**
     * Utility method for dev purposes to analyze unkown info messages.
     */
    bool parseUnknownMessage(byte *header);

    /**
     * Determines wheter the next message is a info message. If yes trie parse it and return the mode number.
     * If it is not, return the message byte.
     */
    bool parseInfoMessage(byte message, EV3SensorInfo *info);

    /**
     *  Parses the first info message (= mode name) for a supported mode
     */
    bool parseModeNameMessage(byte *header, EV3SensorInfo *info);

    /**
     * Parses the symbol name of the SI unit of a supported mode.
     */
    bool parseSymbolNameMessage(byte *header, EV3SensorInfo *info);

    /**
     * Pares the format message containing the format of the data message from sensor -> host.
     */
    bool parseFormatMessage(byte *header, EV3SensorInfo *info);

    /**
     *  Parses the second info message (= mode raw sensor readings) for a supported mode
     */
    bool parseModeRangeMessage(byte *header, EV3SensorInfo *info);
    /**
     * Parses the next uart speed from the stream.
     */
    bool parseSpeed(byte header, EV3SensorConfig *config);

    /**
     * Parses the mode counts from the stream.
     */
    bool parseModeCount(byte header, EV3SensorConfig *config);

    /**
     * Parses the type of  sensor from the stream.
     * If configures, also waits for the unique type byte to come.
     */
    bool parseType(byte message, EV3SensorConfig *config);

    /**
     * Utlity method the read the next available byte from the connection.
     */
    byte readNextAvailableByte();

    void setBaudrate(uint8_t baud);
    static void sensorThread(void *parameter);
    void initSensor(EvoSensorPort *sensor);
};
#endif