#ifndef DD_OLED_DISPLAY_H
#define DD_OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDDisplay {
    private:
        int screenWidth;
        int screenHeight;
        int oledReset;
        Adafruit_SSD1306 *displayModule;

    public:
        OLEDDisplay(int screenWidth, int screenHeight, int oledReset);
        void begin();
        void showMessage(String message);
};

#endif