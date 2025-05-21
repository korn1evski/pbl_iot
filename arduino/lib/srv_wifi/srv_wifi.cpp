#include "env.h"
#include "srv_wifi.h"
#include "srv_global_store.h"


bool connectToWiFi(const char* ssid, const char* password) {
    OLEDDisplay display = *getOLEDDisplay();
    display.showMessage("Connecting WiFi...");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        String dots = "";
          for (int i = 0; i < (attempts % 4); i++) {
            dots += '.';
          }
        display.showMessage("Connecting WiFi" + dots);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected");
        return true;
    } else {
        Serial.println("\nWiFi connection failed");
        display.showMessage("WiFi failed");
        return false;
    }
}

void disconnectFromWiFi() {
    WiFi.disconnect();
    Serial.println("WiFi disconnected");
}

void sendToServer(String uid, String room) {
  OLEDDisplay display = *getOLEDDisplay();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(SERVER_URL);
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
      http.end();
    
      http.begin(SERVER_URL);

      String payload = "{\"rfid_card_id\":\"" + uid + "\",\"room\":\"" + room + "\"}";
      httpResponseCode = http.POST(payload);

      if (httpResponseCode == 200) {
        String response = http.getString();

        int start = response.indexOf(":\"") + 2;
        int end = response.indexOf("\"", start);
        String message = response.substring(start, end);

        display.showMessage(message);
      } else {
        display.showMessage("Server error");
      }

      http.end();
  } else {
    display.showMessage("WiFi failed");
  }
}