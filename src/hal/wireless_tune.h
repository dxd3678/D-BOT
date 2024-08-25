#include <Stream.h>
#include <WiFiUDP.h> 
#include <WiFi.h>

class CommanderWirelessGlue: public Stream {

public:

    CommanderWirelessGlue(uint16_t localPort = 4242);
    ~CommanderWirelessGlue();

    void begin(const char* ssid, const char* password);

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
    WiFiUDP _udp;
    IPAddress _remoteIP;
    uint16_t _remotePort;
    uint16_t _localPort;
    int _packetSize;
    uint8_t _packetBuffer[255];
    size_t _packetIndex;
    // Handles incoming probe messages
     void receivePacket();
};