/* Copyright 2020 Electrical Engineering Enterprise Group.
 *  ESP-EP.12 DATA Logger by ggSpread Sheet  
 *  
 *  Dev.Jukrapun Chitpong
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureAxTLS.h>
ESP8266WiFiMulti WiFiMulti;

//------ Config WiFi ------
#define SSID_1    "Your_SSID1"
#define PASS_1    "Your_PASSWORD1"


void setup() {
  Serial.end();
  Serial.begin(115200);
  delay(10);
  SetWiFi();
  CheckWiFi();

}

void loop(){
  CheckWiFi();
  //GG_ScriptSheet();
  delay(5000);
}

void GG_ScriptSheet(){
  // YOUR SCRIPT = 
  // U can test script by fill:   /?&FIELD1=16&FIELD2=18  
  
  axTLS::WiFiClientSecure client;
  const char* HOST = "script.google.com";
  const char* GScriptId = "";  
  //float TEMP HUMD
  float TEMP = (random(2,50))/3.00;
  float HUMD = (random(20,80))/3.00;
  String url32 = String("/macros/s/") + GScriptId + "/exec?&FIELD1="+(String)TEMP + "&FIELD2="+(String) HUMD;
  Serial.print("Client.Connecting...");

  if (client.connect(HOST, 443)) {
    client.println("GET " + String(url32) + " HTTP/1.0"); //HTTP/1.0 OK sent LINEnotify and GoogleSheet
    client.println("Host: " + String(HOST));
    client.println("User-Agent: ESP8266\r\n");
    client.println("Connection: close\r\n\r\n");
    //client.println(true ? "" : "Connection: close\r\n");
    //client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Type: application/json");    
    //2client.println("Connection: close");    
    client.println("Content-Length: " + String(url32.length()));
    client.println();
    //client.println(postData);
    client.print("\r\n\r\n");
    Serial.print("Response...");  
  }
  Serial.println("OK !!!");  
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
