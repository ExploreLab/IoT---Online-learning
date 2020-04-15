/* Copyright 2018 Electrical Engineering Enterprise Group.
 *  ESP-EP.8_LINEnotify
 *  
 *  Dev.Jukrapun Chitpong
 */

#include <WiFiClientSecureAxTLS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

// WiFi Access Config
#define SSID_1 "HOME_123"        /*Your_SSID*/
#define PASS_1 "CAT123"    /*Your_PASSWORD*/

// LINE Access_Token config
#define LINE_TOKEN "zVismzFDYNfkQHyKoDOgNk2sjqDnSfe01SkMUOvzh8R"
/* TOKEN
S6Jnp29YgA7UaXTWZxGWD8REr2F0X5iK9yakcD98SX3*/

String Your_ID1_ID2 = "Your_123_678";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.print("\n\nElectricl Engineering Enterprise Group\n");
  WiFiMulti.addAP(SSID_1, PASS_1);
  WiFiMulti.addAP("EEEG Co.,Ltd", "VLAD@2018");
  WiFiMulti.addAP("AndroidAP", "ifmd0883");

  Serial.println("Connecting Wifi...");
  delay(2000);
  CheckWiFi();
}

void loop() {
  CheckWiFi();
  LINE_Notify(Your_ID1_ID2);
  delay(2000);
}

void CheckWiFi() {
  if (WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
}

void LINE_Notify(String Message) {
  axTLS::WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  } else {}

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + Message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + Message;

  client.print(req);
  delay(20);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  Serial.println("Send Successfully");
}


