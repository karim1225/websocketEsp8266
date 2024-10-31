#include "Database.h"

Database::Database(const char* filename) : filename(filename) {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    loadData(); 
}

void Database::loadData() {
    File file = SPIFFS.open(filename, "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    size_t size = file.size();
    if (size > 1024) {
        Serial.println("File is too large");
        file.close();
        return;
    }

    String fileContent;
    while (file.available()) {
        fileContent += (char)file.read();
    }

    auto error = deserializeJson(doc, fileContent);
    if (error) {
        Serial.println("Failed to parse JSON");
    }

    file.close();
}

void Database::saveData() {
    File file = SPIFFS.open(filename, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to file");
    }

    file.close();
}

void Database::updateValue(const char* key, const char* value) {
    doc[key] = value; 
    saveData(); 
}

String Database::getValue(const char* key) {
    return doc[key].as<String>(); 
}

// تابع برای ذخیره‌سازی struct
void Database::saveStruct(const char* key, const void* data, size_t size) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    JsonArray jsonArray = doc.createNestedArray(key);

    for (size_t i = 0; i < size; i++) {
        jsonArray.add(bytes[i]); 
    }

    saveData(); 
}

void* Database::getStruct(const char* key, size_t size) {
    static uint8_t buffer[128]; 
    JsonArray jsonArray = doc[key].as<JsonArray>();

    for (size_t i = 0; i < size && i < jsonArray.size(); i++) {
        buffer[i] = jsonArray[i].as<uint8_t>();
    }

    return buffer; 
}

