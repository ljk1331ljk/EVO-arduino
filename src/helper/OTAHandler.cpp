#include "OTAHandler.h"

OTAHandler::OTAHandler(const char *ssid, const char *wifiPassword, const char *otaPassword)
    : _ssid(ssid), _wifiPassword(wifiPassword), _otaPassword(otaPassword) {}

void OTAHandler::begin(OTAMode mode, const char *hostname)
{
    _mode = mode;
    if (hostname && strlen(hostname) > 0)
        _hostname = hostname;

    setupWiFiEvents();

    if (_mode == AP_MODE)
        startAP_NoBlock();
    else
        connectWiFi_NoBlock();

    // Start a background task that repeatedly calls poll()
    startPollTask(); // default: 4096 stack, prio 1, core 1

    Serial.println("[OTA] begin(): non-blocking; poll task started.");
}

void OTAHandler::setupWiFiEvents()
{
    _gotIpHandler = WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t)
                                 {
        if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
            Serial.printf("[WiFi] GOT_IP: %s\n", WiFi.localIP().toString().c_str());
            if (!_otaInitAttempted) initOTAandMDNS();
        } });
    _discHandler = WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t)
                                {
        if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
            Serial.println("[WiFi] DISCONNECTED");
        } });
}

void OTAHandler::connectWiFi_NoBlock()
{
    WiFi.mode(WIFI_STA);
    if (_wifiPassword && strlen(_wifiPassword) > 0)
        WiFi.begin(_ssid, _wifiPassword);
    else
        WiFi.begin(_ssid);
    WiFi.setTxPower(WIFI_POWER_19_5dBm);
    Serial.printf("[WiFi] STA connecting to %s ... (non-blocking)\n", _ssid);
}

void OTAHandler::startAP_NoBlock()
{
    WiFi.mode(WIFI_AP);
    bool ok = (_wifiPassword && strlen(_wifiPassword) > 0) ? WiFi.softAP(_ssid, _wifiPassword)
                                                           : WiFi.softAP(_ssid);
    if (ok)
    {
        Serial.printf("[WiFi] AP '%s' IP: %s\n", _ssid, WiFi.softAPIP().toString().c_str());
        if (!_otaInitAttempted)
            initOTAandMDNS();
    }
    else
    {
        Serial.println("[WiFi] Failed to start AP");
    }
}

void OTAHandler::initOTAandMDNS()
{
    if (_otaInitAttempted)
        return;
    _otaInitAttempted = true;

    ArduinoOTA.setHostname(_hostname);
    if (_otaPassword && strlen(_otaPassword) > 0)
        ArduinoOTA.setPassword(_otaPassword);
    else
        ArduinoOTA.setPassword(nullptr);

    ArduinoOTA
        .onStart([]()
                 { Serial.println("[OTA] Start"); })
        .onEnd([]()
               { Serial.println("\n[OTA] End"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    {
          uint8_t pct = total ? (progress * 100U / total) : 0;
          Serial.printf("[OTA] Progress: %u%%\r", pct); })
        .onError([](ota_error_t error)
                 {
          Serial.printf("\n[OTA] Error[%u]: ", error);
          if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
          else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
          else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
          else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
          else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

    bool mdnsOk = MDNS.begin(_hostname); // STA or AP
    if (mdnsOk)
    {
        MDNS.setInstanceName(_hostname);
        MDNS.addService("arduino", "tcp", 3232);
        // MDNS.addService("http", "tcp", 80);
        Serial.printf("[mDNS] %s.local started\n", _hostname);
    }
    else
    {
        Serial.println("[mDNS] Failed to start (OTA works by IP).");
    }

    ArduinoOTA.begin();
    _otaReady = true;

    if (_mode == AP_MODE)
        Serial.printf("[OTA] Ready (AP). %s.local / %s\n",
                      _hostname, WiFi.softAPIP().toString().c_str());
    else
        Serial.printf("[OTA] Ready (STA) at %s (%s.local)\n",
                      WiFi.localIP().toString().c_str(), _hostname);
}

void OTAHandler::poll()
{
    if (_otaReady)
        ArduinoOTA.handle();
}

// -------- Poll task control --------
void OTAHandler::startPollTask(uint16_t stack, UBaseType_t prio, BaseType_t core)
{
    if (_pollTaskHandle)
        return; // already running
    xTaskCreatePinnedToCore(
        OTAHandler::PollTask, "OTA_Poll", stack, this, prio, &_pollTaskHandle, core);
}

void OTAHandler::stopPollTask()
{
    if (_pollTaskHandle)
    {
        vTaskDelete(_pollTaskHandle);
        _pollTaskHandle = nullptr;
    }
}

void OTAHandler::PollTask(void *param)
{
    auto *self = static_cast<OTAHandler *>(param);
    for (;;)
    {
        self->poll();
        vTaskDelay(pdMS_TO_TICKS(10)); // ~100 Hz
    }
}

String OTAHandler::ipString() const
{
    return (_mode == AP_MODE) ? WiFi.softAPIP().toString() : WiFi.localIP().toString();
}
