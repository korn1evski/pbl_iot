#include "config.h"
#include "srv_global_store.h"

GlobalStore globalStore {
    .rfid = nullptr
};

void initGlobalStore() {
    globalStore.rfid = new RFID(RFID_SS_PIN, RFID_RST_PIN, RFID_SCK_PIN, RFID_MOSI_PIN, RFID_MISO_PIN, RFID_IRQ_PIN);
    globalStore.rfid->begin();
}

RFID* getRFID() {
    return globalStore.rfid;
}