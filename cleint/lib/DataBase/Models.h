#ifndef MODELS_H
#define MODELS_H


struct GameSetting {
    int health;
    int ammo;
    int timer;
};
struct DeviceInfo {
    int type;//0 is gun,1 is vest,2 is headband
    int id;
    uint32_t meshId;
};


#endif