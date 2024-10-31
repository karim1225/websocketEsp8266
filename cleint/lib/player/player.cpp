#include "player.h"

Player::Player(int rxPin, int txPin) {
    softSerial = new SoftwareSerial(rxPin, txPin);
    player = new DY::Player(softSerial);
}

void Player::init() {
    player->begin();
    Serial.begin(9600);
    player->setVolume(30);
}

void Player::playFile(char path[], int volume) {
    player->setVolume(volume);
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::startup(int volume ) {
    player->setVolume(volume);
    char path[] = "/startup.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::shoot(int volume ) {
    player->setVolume(volume);
    char path[] = "/shoot.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::reload(int volume ) {
    player->setVolume(volume);
    char path[] = "/reload.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::start_game(int volume ) {
    player->setVolume(volume);
    char path[] = "/gogo.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::hurt(int volume ) {
    player->setVolume(volume);
    char path[] = "/hurt.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::empty(int volume ) {
    player->setVolume(volume);
    char path[] = "/empty.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::game_over(int volume ) {
    player->setVolume(volume);
    char path[] = "/game-over.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}
void Player::id_changed(int volume ) {
    player->setVolume(volume);
    char path[] = "/id-changed.mp3";
    player->playSpecifiedDevicePath(DY::Device::Flash, path);
}

void Player::stop(){
    player->stop();
}
