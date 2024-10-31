#include "Globals.h" 
#include "MainFunctions.h"
#include "lcd.h"
#include "player.h"
#include "led.h"
#include "ir.h"
#include "MeshNetwork.h"
#include "Database.h"

Database database("/game_data.json");
MeshNetwork meshNetwork;
Player player(DY_PLAYER_RX_PIN, DY_PLAYER_TX_PIN);
Lcd lcd;
Led led(LED_COUNTS, LED_PIN);
Ir ir(IR_SENDER_PIN, IR_RECEIVER_PIN);

void setup() {
    Serial.begin(115200);
    setupMainFunctions(meshNetwork,database,lcd,led,player,ir);  
}

void loop() {   
    meshNetwork.update();
    delay(10);
}
