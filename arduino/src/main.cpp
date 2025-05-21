#include <WiFi.h>
#include <HTTPClient.h>
#include <MFRC522.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// ------------------ OLED Setup ------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ------------------ WiFi Credentials ------------------
const char* ssid = "StarNet - gusev.67";
const char* password = "48575443FC4635A4";

// ------------------ Server ------------------
const char* serverIP = "192.168.100.38"; // Replace with your MacBook's IP
const char* serverPort = "8000"; // Replace with your server port
const char* room = "101"; // Static value for now
// ------------------ RFID ------------------
#define RST_PIN 4
#define SS_PIN  5
MFRC522 rfid(SS_PIN, RST_PIN);

// ------------------ Show message on OLED ------------------
void showMessage(String message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println(message);
  display.display();
}

// ------------------ HTTP Send Function ------------------
void sendToServer(String uid, String room) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://" + String(serverIP) + ":" + String(serverPort) + "/api/health");
    // http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.GET();
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    
      http.begin("http://" + String(serverIP) + ":" + String(serverPort) + "/api/attendances/check");

    String payload = "{\"rfid_card_id\":\"" + uid + "\",\"room\":\"" + room + "\"}";
    httpResponseCode = http.POST(payload);

    if (httpResponseCode == 200) {
      String response = http.getString();

      // Basic JSON response parsing
      int start = response.indexOf(":\"") + 2;
      int end = response.indexOf("\"", start);
      String message = response.substring(start, end);
      showMessage(message);
    } else {
      showMessage("Server error");
    }

    http.end();
  } else {
    showMessage("WiFi failed");
  }
}

// ------------------ Setup ------------------
void setup() {
  Serial.begin(115200);

  // Init SPI *BEFORE* RFID
  SPI.begin();             // SCK=18, MISO=19, MOSI=23 by default
  rfid.PCD_Init();         // Initialize RC522 reader
  Serial.println("RFID ready");

  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }
  display.clearDisplay();
  display.display();
  showMessage("Connecting WiFi...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  showMessage("Scan your card...");
}

// ------------------ Loop ------------------
void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(100);
    return;
  }

  // Read UID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  // Static values for now (can replace later)

  sendToServer(uid, room);

  delay(2000);
  showMessage("Scan your card...");

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
