// Globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include "MeshNetwork.h"      
#include "Database.h" 
#include "Lcd.h" 
#include "Led.h" 
#include "Player.h" 
#include "Ir.h" 

extern MeshNetwork meshNetwork;
extern Database database;
extern Lcd lcd;
extern Led led;
extern Player player;
extern Ir ir;

extern uint16_t total_ammo;
extern uint16_t ammo;
extern uint16_t health;
extern uint16_t timer;
extern uint16_t sAddress;
extern uint8_t sCommand;

#define DY_PLAYER_RX_PIN 33  
#define DY_PLAYER_TX_PIN 32 

#define IR_SENDER_PIN 21
#define IR_RECEIVER_PIN 23

#define LED_PIN 16
#define LED_COUNTS 1

#define SHOOT_BTN 13
#define RELOAD_BTN 12
#define LASER_BTN 14

#define   MESH_PREFIX     "NoaLaserTag"
#define   MESH_PASSWORD   "12345678"
#define   MESH_PORT       5555

// #define STATION_SSID "dlink-A607"
// #define STATION_PASSWORD "RXP#4SN%UQS6"
#define STATION_SSID "ghasemiMobile"
#define STATION_PASSWORD "12Karim12!@"
#define HOSTNAME "WebSocket_Bridge"

#define DEVICE_TYPE 0   //0 is gun,1 is vest,2 is headband 
#define DEVICE_ID "1"


#endif // GLOBALS_H
