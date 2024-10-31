#include "Led.h"

const uint32_t Led::RED = Adafruit_NeoPixel::Color(255, 0, 0);
const uint32_t Led::GREEN = Adafruit_NeoPixel::Color(0, 255, 0);
const uint32_t Led::BLUE = Adafruit_NeoPixel::Color(0, 0, 255);
const uint32_t Led::YELLOW = Adafruit_NeoPixel::Color(255, 255, 0);
const uint32_t Led::WHITE = Adafruit_NeoPixel::Color(255, 255, 255);
const uint32_t Led::OFF = Adafruit_NeoPixel::Color(0, 0, 0);

Led::Led(int numLeds, int pin) : np(numLeds, pin, NEO_GRB + NEO_KHZ800), numLeds(numLeds) {}

void Led::begin() {
    np.begin();
}

void Led::setLedColor(uint32_t color) {
    for (int i = 0; i < numLeds; i++) {
        np.setPixelColor(i, color);
    }
    np.show();
}

void Led::blinkLed(uint32_t color, int times, int delay_ms) {
    for (int i = 0; i < times; i++) {
        setLedColor(color);
        delay(delay_ms);
        setLedColor(OFF);
        delay(delay_ms);
    }
    setLedColor(BLUE);  
}
