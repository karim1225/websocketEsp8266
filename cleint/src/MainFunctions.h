// MainFunctions.h
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include <ArduinoJson.h>     
#include "Globals.h"
#include "OneButton.h" 

void newConnectionCallbackMesh(uint32_t nodeId);
void meshReceivedCallback(uint32_t from, String &msg);
void setupMainFunctions(MeshNetwork &meshNetwork, Database &database,Lcd& lcd,Led& led,Player& player,Ir& ir);
void startGameTimerTask(int time);




#endif // MAINFUNCTIONS_H
