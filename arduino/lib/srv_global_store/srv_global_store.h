#ifndef SRV_GLOBAL_STORE_H
#define SRV_GLOBAL_STORE_H

#include "dd_rfid.h"

struct GlobalStore {
    RFID *rfid;
};

extern GlobalStore globalStore;

void initGlobalStore();
RFID* getRFID();

#endif