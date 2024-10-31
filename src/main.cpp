#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "WebSocketHandler.h"


const char* ssid = "ghasemiMobile";
const char* password = "12Karim12!@";
WebSocketHandler webSocketHandler("192.168.181.209", 3000);

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
}
void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_TEXT: {
            DynamicJsonDocument doc(1024);
            auto error = deserializeJson(doc, payload);
            if (error) {
                Serial.println("Failed to parse JSON");
                return;
            }
            const char* message = doc["message"];
            Serial.println(message);
            Serial.println("Received: ");
            serializeJson(doc, Serial);
            Serial.println();
            break;
        }

        case WStype_BIN:
            // پردازش داده‌های باینری
            break;
    }
}
void setup() {
    Serial.begin(9600);
    connectToWiFi();
    webSocketHandler.begin();
    webSocketHandler.webSocket.onEvent(webSocketEvent);
}

void loop() {   
     webSocketHandler.loop();


}
