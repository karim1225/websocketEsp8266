#include "WebSocketHandler.h"

WebSocketHandler::WebSocketHandler(const char* server, uint16_t port)
    : websocket_server(server), websocket_port(port),lcd(nullptr) {
    }

void WebSocketHandler::begin() {
    webSocket.begin(websocket_server, websocket_port, "/");
    webSocket.onEvent(WebSocketHandler::webSocketEvent);
    webSocket.setReconnectInterval(5000);  // تلاش مجدد پس از 5 ثانیه
}

void WebSocketHandler::loop() {
    webSocket.loop();
}

void WebSocketHandler::sendMessage(String message) {
    webSocket.sendTXT(message);
}
void WebSocketHandler::setLcd(Lcd* lcd) {
    this->lcd = lcd;  
}

void WebSocketHandler::webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_TEXT: {
            String message = String((char *)payload).substring(0, length);
            DynamicJsonDocument doc(1024);
            auto error = deserializeJson(doc, message);
            if (error) {
                Serial.println("Failed to parse JSON");
                return;
            }
            const char* action = doc["action"];
            if (strcmp(action, "startGame") == 0) {
               
                Serial.println("startGame");
            }
            break;
        }

        case WStype_BIN:
            // پردازش داده‌های باینری
            break;
    }
}
