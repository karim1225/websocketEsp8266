#ifndef DATABASE_H
#define DATABASE_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "Models.h"

class Database {
public:
    Database(const char* filename);
    void loadData();
    void saveData();
    void updateValue(const char* key, const char* value);
    String getValue(const char* key);

    void saveStruct(const char* key, const void* data, size_t size);
    void* getStruct(const char* key, size_t size);

    void seveGameSetting(GameSetting data);
    GameSetting getGameSetting();



private:
    const char* filename;
    JsonDocument doc;
};

#endif
