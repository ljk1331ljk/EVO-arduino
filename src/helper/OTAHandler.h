#pragma once
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>

enum OTAMode
{
    STA_MODE,
    AP_MODE
};

class OTAHandler
{
public:
    OTAHandler(const char *ssid, const char *wifiPassword, const char *otaPassword);
    void begin(OTAMode mode, const char *hostname = nullptr);

    // If you want manual polling in loop() as well, you still can call this, it's safe.
    void poll();

    // Optional: control the poll task
    void startPollTask(uint16_t stack = 4096, UBaseType_t prio = 1, BaseType_t core = 1);
    void stopPollTask();

    String ipString() const;
    bool isReady() const { return _otaReady; }

private:
    void connectWiFi_NoBlock();
    void startAP_NoBlock();
    void initOTAandMDNS();
    void setupWiFiEvents();

    static void PollTask(void *param); // <-- task body

    const char *_ssid;
    const char *_wifiPassword;
    const char *_otaPassword;
    const char *_hostname = "esp32";
    OTAMode _mode = STA_MODE;

    volatile bool _otaReady = false;
    volatile bool _otaInitAttempted = false;

    wifi_event_id_t _gotIpHandler = 0;
    wifi_event_id_t _discHandler = 0;

    TaskHandle_t _pollTaskHandle = nullptr; // <-- task handle
};
