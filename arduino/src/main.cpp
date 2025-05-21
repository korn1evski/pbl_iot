#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "env.h"
#include "config.h"
#include "dd_rfid.h"

// ------------------ OLED Setup ------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ------------------ WiFi Credentials ------------------
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// ------------------ Server ------------------
const char* serverIP = SERVER_IP;
const char* serverPort = SERVER_PORT;
const char* room = ESP_READER_CLASSROOM;

// ------------------ RFID ------------------

RFID rfid(RFID_SS_PIN, RFID_RST_PIN, RFID_SCK_PIN, RFID_MOSI_PIN, RFID_MISO_PIN, RFID_IRQ_PIN);

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
  rfid.begin();
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
  if (!rfid.isCardPresent() || !rfid.readCard()) {
    delay(100);
    return;
  }

  // Read UID
  String uid = rfid.getUID();
  uid.toUpperCase();

  sendToServer(uid, room);

  delay(2000);
  showMessage("Scan your card...");

  rfid.stopCrypto1();
}
