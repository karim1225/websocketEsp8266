#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include "lcd.h"

class WebSocketHandler {
public:
    WebSocketHandler(const char* server, uint16_t port);
    void begin();
    void loop();
    void sendMessage(String message);
    void setLcd(Lcd* lcd);

private:
    const char* websocket_server;
    uint16_t websocket_port;
    WebSocketsClient webSocket;
    Lcd* lcd;
    static WebSocketHandler* instance;
    static void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);
};

#endif
