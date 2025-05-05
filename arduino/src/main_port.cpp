#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RFID
#define RST_PIN 4
#define SS_PIN  5
MFRC522 rfid(SS_PIN, RST_PIN);

void showMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println(message);
  display.display();
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.display();
  showMessage("Scan your card...");
}

void loop() {
  // Wait for card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  // Read UID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase(); // Match DB format

  // ⚠️ Mock time for testing
  String timeNow = "13:31";
  String day = "Monday";
  String room = "Room101";

  // Send UID + room + time + day
  String message = uid + "," + room + "," + timeNow + "," + day;
  Serial.println(message);

  // Wait for response from Python
  unsigned long timeout = millis() + 3000;
  while (!Serial.available()) {
    if (millis() > timeout) {
      showMessage("No response from DB");
      return;
    }
  }

  String response = Serial.readStringUntil('\n');
  showMessage(response); // ✅ show result on OLED (don't echo to Serial)

  delay(2000); // Show message for 2 seconds
  showMessage("Scan your card...");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}


