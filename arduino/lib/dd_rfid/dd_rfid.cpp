#include <Arduino.h>
#include <SPI.h>
#include "dd_rfid.h"

RFID::RFID(int ssPin, int rstPin, int sdaPin, int sckPin, int mosiPin, int misoPin, int irqPin) {
    this->sdaPin = sdaPin;
    this->sckPin = sckPin;
    this->mosiPin = mosiPin;
    this->misoPin = misoPin;
    this->irqPin = irqPin;
    this->ssPin = ssPin;
    this->rstPin = rstPin;
    rfid_module = new MFRC522(ssPin, rstPin);
}

void RFID::begin() {
    SPI.begin(sckPin, misoPin, mosiPin, ssPin);
    rfid_module->PCD_Init();
}

bool RFID::isCardPresent() {
    return rfid_module->PICC_IsNewCardPresent();
}

bool RFID::readCard() {
    return rfid_module->PICC_ReadCardSerial();
}

String RFID::getUID() {
    String uid = "";
    for (byte i = 0; i < rfid_module->uid.size; i++) {
        uid += String(rfid_module->uid.uidByte[i], HEX);
    }
    return uid;
}

void RFID::stopCrypto1() {
    rfid_module->PICC_HaltA();
    rfid_module->PCD_StopCrypto1();
}