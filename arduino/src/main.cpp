#include "env.h"
#include "config.h"
#include "srv_wifi.h"
#include "srv_global_store.h"

void setup() {
  Serial.begin(115200);
  
  initGlobalStore();

  RFID rfid = *getRFID();
  OLEDDisplay display = *getOLEDDisplay();

  rfid.begin();
  Serial.println("RFID ready");

  display.begin();
  Serial.println("OLED ready");

  if (!connectToWiFi(WIFI_SSID, WIFI_PASSWORD)) {
    display.showMessage("Retrying WiFi...");
    delay(5000);
    ESP.restart();
  }

  display.showMessage("Scan your card...");
}

void loop() {
  RFID rfid = *getRFID();
  OLEDDisplay display = *getOLEDDisplay();
  
  if (!rfid.isCardPresent() || !rfid.readCard()) {
    delay(100);
    return;
  }

  String uid = rfid.getUID();
  uid.toUpperCase();

  sendToServer(uid, ESP_READER_CLASSROOM);

  delay(2000);
  display.showMessage("Scan your card...");

  rfid.stopCrypto1();
}
