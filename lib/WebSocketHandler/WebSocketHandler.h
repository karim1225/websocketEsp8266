#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <WebSocketsClient.h>
#include <ArduinoJson.h>

class WebSocketHandler {
public:
    WebSocketsClient webSocket;
    WebSocketHandler(const char* server, uint16_t port);
    void begin();
    void loop();

private:
    const char* websocket_server;
    uint16_t websocket_port;
};

#endif
