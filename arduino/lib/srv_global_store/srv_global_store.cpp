#include "config.h"
#include "srv_global_store.h"

GlobalStore globalStore {
    .rfid = nullptr,
    .oledDisplay = nullptr
};

void initGlobalStore() {
    globalStore.rfid = new RFID(RFID_SS_PIN, RFID_RST_PIN, RFID_SCK_PIN, RFID_MOSI_PIN, RFID_MISO_PIN, RFID_IRQ_PIN);
    globalStore.oledDisplay = new OLEDDisplay(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, OLED_RESET_PIN);
}

RFID* getRFID() {
    return globalStore.rfid;
}

OLEDDisplay* getOLEDDisplay() {
    return globalStore.oledDisplay;
}