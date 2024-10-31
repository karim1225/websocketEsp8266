#ifndef PLAYER_H
#define PLAYER_H

#include <DYPlayerArduino.h>
#include <SoftwareSerial.h>

class Player {
    public:
        Player(int rxPin, int txPin);
        void init();
        void playFile(char path[], int volume=30);
        void startup(int volume=30);
        void shoot(int volume=30);
        void reload(int volume=30);
        void start_game(int volume=30);
        void hurt(int volume=30);
        void empty(int volume=30);
        void game_over(int volume=30);
        void id_changed(int volume=30);
        void stop();
    private:
        SoftwareSerial* softSerial;
        DY::Player* player;        
};
#endif