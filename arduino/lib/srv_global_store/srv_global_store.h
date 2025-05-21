#ifndef SRV_GLOBAL_STORE_H
#define SRV_GLOBAL_STORE_H

#include "dd_rfid.h"
#include "dd_oled_display.h"

struct GlobalStore {
    RFID *rfid;
    OLEDDisplay *oledDisplay;
};

extern GlobalStore globalStore;

void initGlobalStore();
RFID* getRFID();
OLEDDisplay* getOLEDDisplay();

#endif