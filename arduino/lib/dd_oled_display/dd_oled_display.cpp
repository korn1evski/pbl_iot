#include "dd_oled_display.h"

OLEDDisplay::OLEDDisplay(int screenWidth, int screenHeight, int oledReset) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->oledReset = oledReset;
    displayModule = new Adafruit_SSD1306(screenWidth, screenHeight, &Wire, oledReset);
}

void OLEDDisplay::begin() {
    if (!displayModule->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED failed");
        while (true);
    }

    displayModule->clearDisplay();
    displayModule->display();
}

void OLEDDisplay::showMessage(String message) {
    displayModule->clearDisplay();
    displayModule->setTextSize(1);
    displayModule->setTextColor(SSD1306_WHITE);

    int16_t x1, y1;
    uint16_t w, h;

    displayModule->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);

    int16_t x = (displayModule->width() - w) / 2;
    int16_t y = (displayModule->height() - h) / 2;

    displayModule->setCursor(x, y);
    displayModule->println(message);
    displayModule->display();
}