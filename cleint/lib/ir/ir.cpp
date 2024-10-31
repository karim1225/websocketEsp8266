#include "ir.h"
#include <Arduino.h>
#include <IRremote.hpp>


Ir::Ir(int irSendPin, int irRecvPin) {
    IrSender.begin(irSendPin, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
    IrReceiver.begin(irRecvPin);
}

void Ir::init() {
    Serial.begin(115200);
    Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
}

void Ir::send(uint16_t sAddress,uint8_t sCommand) { 
   IrSender.sendNEC(sAddress, sCommand,0);
}

void Ir::startReciveTask() {
    xTaskCreatePinnedToCore(
        [](void *pvParameters) {
            Ir *ir = static_cast<Ir*>(pvParameters);  
            ir->IRReciveTask(); 
        },
        "IRReciveTask",      
        4096,                
        this,               
        1,                   
        NULL,
        0                
    );
}
void Ir::IRReciveTask() {
    Serial.begin(115200);
    while (true) { 
     if (IrReceiver.decode()) {
         Serial.println(IrReceiver.decodedIRData.command, HEX);
         Serial.println(IrReceiver.decodedIRData.address, HEX);
         IrReceiver.resume();
     }
        vTaskDelay(300 / portTICK_PERIOD_MS);  
    }
}
