#include "MainFunctions.h"

uint16_t total_ammo = 300;
uint16_t ammo = 30;
uint16_t health = 100;
uint16_t timer = 30;
uint16_t magazines = total_ammo / ammo;

uint16_t sAddress = 0x30;
uint8_t sCommand = 0x34;

OneButton shoot_btn(SHOOT_BTN,true);
OneButton reload_btn(RELOAD_BTN,true);
OneButton laser_btn(LASER_BTN,true);


volatile bool shootFlag = false; // Flag for shoot action
volatile bool reloadFlag = false; // Flag for reload action
unsigned long lastShootTime = 0;
const unsigned long shootDelay = 500;
unsigned long lastReloadTime = 0;
const unsigned long reloadDelay = 500;

// Timer
TaskHandle_t timerTaskHandle = NULL;
unsigned long previousMillis = 0;
const long interval = 1000; 
unsigned long countdownTime = 30 * 60; 
bool isStartTimer = false;

// Functions
void sendDeviceInfo(){
    JsonDocument doc; 
    doc["action"] = "deviceInfo";
    JsonObject data = doc["data"].to<JsonObject>();
    data["id"] = database.getValue("id").toInt();
    data["type"] = database.getValue("type").toInt();
    data["meshId"] = meshNetwork.mesh.getNodeId();
    String jsonString;
    serializeJson(doc, jsonString);
    meshNetwork.mesh.sendBroadcast(jsonString);
}
void changeDeviceIdMesh( JsonObject data){
    int ID = data["id"];
    int deviceType = String(DEVICE_TYPE).toInt();
    int TYPE = data["type"];
    if(TYPE != deviceType){
        return;
    }
    database.loadData();
    String devive_id = database.getValue("id");
    if(devive_id !="null"){
        if(devive_id.toInt() == ID ){
            String newID = data["new_id"];
            database.updateValue("id",newID.c_str());
            player.id_changed();
            Serial.println("id changed");
            sendDeviceInfo();
        }
    }
  
}

    // Timer fn
void stopGameTimerTask() {
    if(isStartTimer){
        isStartTimer = false;    
        countdownTime = 0; 
        vTaskDelete(timerTaskHandle); 
        timerTaskHandle = NULL;
    } 
}
void gameTimerTask(void *pvParameters) {
    while (true) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            if (countdownTime > 0) {
                countdownTime--; 
            }
            if (countdownTime <= 0) {
                Serial.println("Timer finished!");
                stopGameTimerTask();
                break; 
            }
            int minutes = countdownTime / 60;
            int seconds = countdownTime % 60;
            lcd.drawTimer(minutes, seconds);  
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}
void startGameTimerTask(int time){
        countdownTime = time;  
        isStartTimer = true;
        BaseType_t result = xTaskCreatePinnedToCore(gameTimerTask, "TimerTask", 4096,NULL, 1, &timerTaskHandle,1);
        if (result != pdPASS) {
            Serial.println("Failed to create timer task!");
        }
    
}

    // btn fn
ICACHE_RAM_ATTR void checkShootTicks() {
  shoot_btn.tick();
}
ICACHE_RAM_ATTR void checkReloadTicks() {
  reload_btn.tick();
}
ICACHE_RAM_ATTR void checkLaserTicks() {
  laser_btn.tick();
}
void shootBtnClick() {
    if (ammo > 0 ) {
        player.shoot();
        ir.send(sAddress, sCommand);
        ammo -= 1;
        lcd.drawAmmo(magazines, ammo);
        lastShootTime = millis();  
    } else {
        player.empty();
    }
    
}
void reloadBtnClick() {
    if (magazines > 0 && ammo == 0) {
        ammo = 30;
        magazines -= 1;
        lcd.drawAmmo(magazines, ammo);
        player.reload();
        lastReloadTime = millis(); 
    } else {
        player.empty();
    }
}


// RecivesCallBack
void meshReceivedCallback(uint32_t from, String &msg) {
    Serial.begin(115200);
    JsonDocument doc; 
    DeserializationError error = deserializeJson(doc, msg);
    if (error) {
        Serial.println("Failed to parse JSON");
        return;
    }
    const char* action = doc["action"];
    if (strcmp(action, "gameSetting") == 0 || strcmp(action, "updateGameSetting") == 0) {
        JsonObject data = doc["data"];
        total_ammo = data["ammo"];  
        health = data["health"];
        timer = data["timer"];      
    }
    if (strcmp(action, "startGame") == 0) {
        startGameTimerTask(timer * 60);
    }
    if (strcmp(action, "stopGame") == 0) {
        stopGameTimerTask();
    }
    if (strcmp(action, "update_device_info") == 0) {
        JsonObject data = doc["data"];
        changeDeviceIdMesh(data);
    }
    if (strcmp(action, "getDeviceInfo") == 0) {
        sendDeviceInfo();
    }
 
    Serial.printf("Mesh Message received from %u: %s\n", from, msg.c_str());
}
void newConnectionCallbackMesh(uint32_t nodeId) {
    Serial.printf("MeshNetwork: New Connection, nodeId = %u\n", nodeId);
}


void setupMainFunctions(MeshNetwork &meshNetwork, Database &database,Lcd& lcd,Led& led,Player& player,Ir& ir) {
   
    meshNetwork.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
    meshNetwork.mesh.onReceive(meshReceivedCallback);
    meshNetwork.mesh.onNewConnection(newConnectionCallbackMesh);
    lcd.init();
    ir.init();
    ir.startReciveTask();
    player.init();

    String idValue = database.getValue("id");
    if (idValue == "null") { 
        String deviceIdStr = String(DEVICE_ID);
        database.updateValue("id", deviceIdStr.c_str()); 
    }

    shoot_btn.attachClick(shootBtnClick);
    shoot_btn.attachClick(reloadBtnClick);
    // pinMode(SHOOT_BTN, INPUT_PULLUP);
    // pinMode(RELOAD_BTN, INPUT_PULLUP);
    // pinMode(LASER_BTN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(SHOOT_BTN), checkShootTicks, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RELOAD_BTN), checkReloadTicks, CHANGE);

}
