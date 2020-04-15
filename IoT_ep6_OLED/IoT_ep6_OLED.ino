#include <Adafruit_GFX.h>
#include <ESP_Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x78>>1);
  display.display();
  delay(2000);
  display.clearDisplay();  
}

void loop() {
  display.setTextSize(1);
  display.setTextColor(WHITE);  
  display.setCursor(8, 8);
  display.print("SmartHouse Welcome");  
  display.setTextSize(2);
  display.setCursor(32, 26);
  display.print("IoT");  
  display.drawRect(24, 22, 86, 40, WHITE); // drawRect(x,y,w,h,color)
  display.display();
  delay(1000);
  display.clearDisplay(); 
}

