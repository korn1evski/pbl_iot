#ifndef SRV_WIFI_H
#define SRV_WIFI_H

#include <WiFi.h>
#include <HTTPClient.h>

bool connectToWiFi(const char* ssid, const char* password);
void disconnectFromWiFi();
void sendToServer(String uid, String room);

#endif