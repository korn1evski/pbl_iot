// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <MFRC522.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <Adafruit_SSD1306.h>
// #include <Adafruit_GFX.h>

// // ------------------ OLED Setup ------------------
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // ------------------ WiFi Credentials ------------------
// const char* ssid = "wifi_name";
// const char* password = "wifi_password";

// // ------------------ Server ------------------
// const char* serverIP = "192.168.0.134"; // Replace with your MacBook's IP

// // ------------------ RFID ------------------
// #define RST_PIN 4
// #define SS_PIN  5
// MFRC522 rfid(SS_PIN, RST_PIN);

// // ------------------ Show message on OLED ------------------
// void showMessage(String message) {
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(WHITE);
//   display.setCursor(0, 20);
//   display.println(message);
//   display.display();
// }

// // ------------------ HTTP Send Function ------------------
// void sendToServer(String uid, String room, String timeNow, String day) {
//   if (WiFi.status() == WL_CONNECTED) {
//     HTTPClient http;
//     http.begin("http://" + String(serverIP) + ":5001/check");
//     http.addHeader("Content-Type", "application/json");

//     String payload = "{\"uid\":\"" + uid + "\",\"room\":\"" + room + "\",\"time\":\"" + timeNow + "\",\"day\":\"" + day + "\"}";
//     int httpResponseCode = http.POST(payload);

//     if (httpResponseCode == 200) {
//       String response = http.getString();

//       // Basic JSON response parsing
//       int start = response.indexOf(":\"") + 2;
//       int end = response.indexOf("\"", start);
//       String message = response.substring(start, end);
//       showMessage(message);
//     } else {
//       showMessage("Server error");
//     }

//     http.end();
//   } else {
//     showMessage("WiFi failed");
//   }
// }

// // ------------------ Setup ------------------
// void setup() {
//   Serial.begin(115200);

//   // Init SPI *BEFORE* RFID
//   SPI.begin();             // SCK=18, MISO=19, MOSI=23 by default
//   rfid.PCD_Init();         // Initialize RC522 reader
//   Serial.println("RFID ready");

//   // Init OLED
//   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//     Serial.println("OLED failed");
//     while (true);
//   }
//   display.clearDisplay();
//   display.display();
//   showMessage("Connecting WiFi...");

//   // Connect to WiFi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");
//   showMessage("Scan your card...");
// }

// // ------------------ Loop ------------------
// void loop() {
//   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
//     delay(100);
//     return;
//   }

//   // Read UID
//   String uid = "";
//   for (byte i = 0; i < rfid.uid.size; i++) {
//     uid += String(rfid.uid.uidByte[i], HEX);
//   }
//   uid.toUpperCase();

//   // Static values for now (can replace later)
//   String room = "Room101";
//   String timeNow = "13:31";
//   String day = "Monday";

//   sendToServer(uid, room, timeNow, day);

//   delay(2000);
//   showMessage("Scan your card...");

//   rfid.PICC_HaltA();
//   rfid.PCD_StopCrypto1();
// }
