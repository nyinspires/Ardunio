#include <SPI.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup() { 
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
}

void loop() {
Serial.println("  !");
display.clearDisplay(); 
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Hello "); 
delay(10000);

}
