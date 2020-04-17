/* Copyright 2018 Electrical Engineering Enterprise Group.
 *  ESP-EP.7_NTP
 *  
 *  Dev.Jukrapun Chitpong
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <time.h>

//WIFI 
ESP8266WiFiMulti wifiMulti;
#define YOUR_SSID "IoT2020"
#define YOUR_PASS "P@ssw123" 


// Config time
int timezone = 7;       // Zone +7 for Thailand
char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;
int  Sec = 0;
void setup() {
  Serial.begin(115200);
  
  /*---- Config WiFi ----*/
  wifiMulti.addAP("Year2020", "1235th");
  wifiMulti.addAP("AndroidAP", "ifmd0883");
  wifiMulti.addAP(YOUR_SSID, YOUR_PASS);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
  Serial.println("WiFi connected!");
  delay(500);  

  /*---- Config Time ----*/
  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }  


}

void loop() {
  ChkWiFi();
  NowString();
  delay(1000);
  if(Sec > 30){
    Serial.print(" OK ");
  }else{
    Serial.print(" NON ");
  }

}

void ChkWiFi(){
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }  
}

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  Serial.println(tmpNow);
  Sec = newtime->tm_sec;
  return tmpNow;

}
