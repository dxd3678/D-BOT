/* 
 *   Copyright (C) 2024 dingmos. All rights reserved.
 */

#include "hal/hal.h"
#include "wireless_tune.h"
#include <Arduino.h>

#define WL_TUNE_MAX_PACKETSIZE  255
// const uint8_t *probe_rsp = (const uint8_t *)"STUDIO_YES";
// const char *probe_msg = "STUDIO_PROBE";
CommanderWirelessGlue::CommanderWirelessGlue( uint16_t localPort) 
  : _localPort(localPort), _packetSize(0), _packetIndex(0), _remotePort(UINT16_MAX)
{
}

CommanderWirelessGlue::~CommanderWirelessGlue() 
{
    // Destructor for cleanup
}

void CommanderWirelessGlue::begin(const char* ssid, const char* password)
{
    // Connect to WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.printf("Connected to WiFi.\n");
    Serial.printf("IP address: %s", WiFi.localIP().toString());
    // Start UDP
    _udp.begin(_localPort);

}

void CommanderWirelessGlue::receivePacket() {
    if ( _udp.parsePacket() > 0) {
        _remoteIP = _udp.remoteIP();
        _remotePort = _udp.remotePort();
        _packetSize = _udp.read(_packetBuffer, WL_TUNE_MAX_PACKETSIZE);
        _packetBuffer[_packetSize + 1] = '\0';
        _packetIndex = 0;

        // Serial.printf("remote: %s:%d - msg: %s size: %d, packet_Index: %d\n", 
        //                     _remoteIP.toString(), _remotePort, _packetBuffer, 
        //                     _packetSize, _packetIndex);
    }
}

int CommanderWirelessGlue::available() {

    if (_packetIndex >= _packetSize) {
        receivePacket();  // Check for a new packet if the current one is fully read
    }

    return  _packetSize - _packetIndex;
}

int CommanderWirelessGlue::read() {

    if (_packetIndex < _packetSize) {
        return _packetBuffer[_packetIndex++];
    } else {
        return -1; // No more data to read
    }
}

int CommanderWirelessGlue::peek() {
    if (_packetIndex < _packetSize) {
        return _packetBuffer[_packetIndex];
    } else {
        return -1; // No more data to peek at
    }
}

void CommanderWirelessGlue::flush() {
    // Nothing to flush in this implementation
}

size_t CommanderWirelessGlue::write(uint8_t data) {
    if (_remotePort != UINT16_MAX) {
        _udp.beginPacket(_remoteIP, _remotePort);
        _udp.write(data);
        return _udp.endPacket();
    } else {
        return 0; // No client to send data to
    }
}

size_t CommanderWirelessGlue::write(const uint8_t* buffer, size_t size) {
    if (_remotePort != UINT16_MAX) {
        _udp.beginPacket(_remoteIP, _remotePort);
        _udp.write(buffer, size);
        return _udp.endPacket();
    } else {
        return 0; // No client to send data to
    }
}