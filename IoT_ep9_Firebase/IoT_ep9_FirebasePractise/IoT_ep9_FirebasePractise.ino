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
#define PROJECT_IO "Your_PROJECT_IO"
#define DATA_SECRET "Your_DATA_SECRET"

// WiFi Access Config
#define SSID_1 "HOME12345"
#define PASS_1 "IoT2020" 

//DHT
#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); 
float t,h;

#include <Adafruit_GFX.h>
#include <ESP_Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.end();
  Serial.begin(115200);
  delay(10);
  SetWiFi();
  CheckWiFi();
  
  Firebase.begin(PROJECT_IO, DATA_SECRET);
  dht.begin();   
  display.begin(SSD1306_SWITCHCAPVCC, 0x78>>1);
  display.display();
  delay(2000);
  display.clearDisplay();    
  
}

void loop() {
  CheckWiFi();
  Inspection_DHT();
  Firebase_SET();
  Firebase_GET();
}


void Inspection_DHT(){
  delay(2000);
  t = dht.readTemperature();
  h = dht.readHumidity();
  Serial.println("Temp: " + String(t) + "\tHumd: " + String(h));
  if(isnan(t) || isnan(h)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void Firebase_SET(){
  //int A = random(0, 100);
  //Firebase.set("VALUE/A", A);
  Firebase.set("DHT/TEMP", t);
  Firebase.set("DHT/HUMD", h);
  delay(1000);
}

void Firebase_GET(){
  //int VALUE_A = Firebase.get("VALUE/A");
  //Serial.println("VALUE/A: " + String(VALUE_A));
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.setCursor(8, 8);
  display.print("SmartFarm Welcome");  
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.println("TEMP:" + String(t));  
  display.print("HUMD:" + String(h));
  //display.drawRect(24, 22, 86, 40, WHITE); // drawRect(x,y,w,h,color)
  display.display();
  delay(1000);
  display.clearDisplay(); 
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
