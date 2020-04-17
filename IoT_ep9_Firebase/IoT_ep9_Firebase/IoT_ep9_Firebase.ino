/* Copyright 2018 Electrical Engineering Enterprise Group.
 *  ESP-EP.9_Firebase
 *  
 *  Dev.Jukrapun Chitpong
 */
 
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;

// FIREBASE NAME/SECRET Config 
#define PROJECT_IO "iotpim-2020.firebaseio.com"
#define DATA_SECRET "arB4v6ZJuFxe18WWqC827Bn5nTVHg2bftni6rzO4"

// WiFi Access Config
#define SSID_1 "HOME12345"
#define PASS_1 "IoT2020" 


void setup() {
  Serial.end();
  Serial.begin(115200);
  delay(10);
  SetWiFi();
  CheckWiFi();
  
  Firebase.begin(PROJECT_IO, DATA_SECRET);
  
}

void loop() {
  CheckWiFi();
  Firebase_SET();
  Firebase_GET();
}

void Firebase_SET(){
  int A = random(0, 100);
  Firebase.set("VALUE/A", A);
  delay(1000);
}

void Firebase_GET(){
  int VALUE_A = Firebase.get("VALUE/A");
  Serial.println("VALUE/A: " + String(VALUE_A));
  delay(1000);
}

void CheckWiFi(){
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
}

void SetWiFi(){
  Serial.print("\n\nElectricl Engineering Enterprise Group\n");
  WiFiMulti.addAP(SSID_1, PASS_1);  
  WiFiMulti.addAP("AndroidAP", "ifmd0883");
  Serial.println("Connecting Wifi...");
  delay(2000);  
  Serial.println("Connecting Wifi...");
  if (WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
