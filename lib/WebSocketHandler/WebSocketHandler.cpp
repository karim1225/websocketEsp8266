#include "WebSocketHandler.h"

WebSocketHandler::WebSocketHandler(const char* server, uint16_t port)
    : websocket_server(server), websocket_port(port) {}

void WebSocketHandler::begin() {
    webSocket.begin(websocket_server, websocket_port, "/");
    webSocket.setReconnectInterval(5000);  // تلاش مجدد پس از 5 ثانیه
}

void WebSocketHandler::loop() {
    webSocket.loop();
}
