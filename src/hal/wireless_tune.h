#include <Stream.h>
#include <WiFiUDP.h> 
#include <WiFi.h>

enum WiFiMode {
    AP_MODE,
    STA_MODE
};

class CommanderWirelessGlue: public Stream {

public:

    CommanderWirelessGlue(uint16_t localPort = 4242);
    ~CommanderWirelessGlue();

    bool begin(const char* ssid, const char* password, WiFiMode mode = STA_MODE);

    // Stream类中必须实现的虚函数
    virtual int available() override;
    virtual int read() override;
    virtual int peek() override;
    virtual void flush() override;

    // 额外定义的函数
    size_t write(uint8_t byte) override;
    size_t write(const uint8_t *buffer, size_t size) override;

    // Enable print and println methods
    using Print::write;
private:
    WiFiServer _server;
    WiFiClient _client;
    IPAddress _remoteIP;
    uint16_t _remotePort;
    uint16_t _localPort;
    int _packetSize;
    uint8_t _packetBuffer[255];
    size_t _packetIndex;

    void acceptClient();
    void receivePacket();
    int handleClientDisconnect();
};