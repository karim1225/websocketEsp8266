#include "MeshNetwork.h"
void MeshNetwork::init(TSTRING ssid, TSTRING password, uint16_t port) {
   Serial.begin(115200);
   mesh.setDebugMsgTypes( ERROR | STARTUP );
   mesh.init(ssid,password,&userScheduler, port);
}
void MeshNetwork::update() {
    mesh.update();
}
