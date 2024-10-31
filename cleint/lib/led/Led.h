#ifndef Led_H
#define Led_H

#include <Adafruit_NeoPixel.h>

class Led {
    public:
        Led(int numLeds, int pin);  
        void begin();                           
        void setLedColor(uint32_t color);       
        void blinkLed(uint32_t color, int times, int delay_ms);  

        static const uint32_t RED;
        static const uint32_t GREEN;
        static const uint32_t BLUE;
        static const uint32_t YELLOW;
        static const uint32_t WHITE;
        static const uint32_t OFF;

    private:
        Adafruit_NeoPixel np;  
        int numLeds;         
};

#endif
