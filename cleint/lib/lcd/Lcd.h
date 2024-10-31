#ifndef LCD_H
#define LCD_H

#include <TFT_eSPI.h> 
extern TFT_eSPI tft;

class Lcd {
    public:
        void init();
        void drawLoadingCircle(int x, int y, int radius, int angle, uint16_t color, int thickness);
        void drawWiFiInfo(String id, int signalStrength);
        void drawAmmo(int magazines, int ammo);
        void drawHelth(int helth);
        void drawGunId(int id, uint16_t color);
        void drawSkull(int num);
        void drawTarget(int num);
        void drawBatteryIcon(int percentage);
        void drawStatusBar();
        void drawVest(bool enable = false);
        void drawHeadBand(bool enable = false);
        void drawHeart();
        void drawBullet();
        void drawCoin(int coin);
        void clearNum(int x, int y, int font);
        void drawTimer(int minutes, int seconds);

    private:
        TFT_eSPI tft;
        char previousTimeStr[6] = "00:00";  
};

#endif
