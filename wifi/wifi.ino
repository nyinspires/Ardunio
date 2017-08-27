#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Picopixel.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//////////////////////
// WiFi Definitions //
//////////////////////
const char ssid[] = "FIRST_FTA_NETWORK";
const char wifipassword[] = "FTANetwork";


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  setupWiFi();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  Serial.println("Setup done");
}



void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    display.setFont();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(n);
    Serial.print(n);
    Serial.println(" networks found");
    display.println(" networks found");
    display.setFont(&Picopixel);
    for (int i = 0; i < n; ++i)
    {

      display.print(i + 1);
      display.print(": ");
      display.print(WiFi.SSID(i));
      display.print(" (");
      display.print(WiFi.RSSI(i));
      display.print(")");
      display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");

      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);

    }
    display.display();
    delay(2000);
    display.clearDisplay();
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}


void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP(ssid, wifipassword);
  IPAddress myIP = WiFi.softAPIP();
  if (result == true)
  {
    Serial.println("Ready");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
  else
  {
    Serial.println("Failed!");
  };
}
