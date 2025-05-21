#ifndef DD_RFID_H
#define DD_RFID_H

#include <MFRC522.h>
#include <SPI.h>

class RFID {
    private:
        int sdaPin;
        int sckPin;
        int mosiPin;
        int misoPin;
        int irqPin;
        int ssPin;
        int rstPin;
        MFRC522 *rfid_module;
    public:
        RFID(int ssPin, int rstPin, int sdaPin = SDA, int sckPin = SCK, int mosiPin = MOSI, int misoPin = MISO, int irqPin = -1);
        void begin();
        void end();
        bool isCardPresent();
        bool readCard();
        String getUID();
        void stopCrypto1();
};

#endif