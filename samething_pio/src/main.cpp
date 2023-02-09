#include <Arduino.h>
#include "WiFi.h"

// WiFi credentials.
const char* WIFI_SSID = "ux-guest202";
const char* WIFI_PASS = "karin120";
// 203A-AC
// Nakanishi

void setup()
{
    Serial.begin(9600);
    // Giving it a little time because the serial monitor doesn't
    // immediately attach. Want the firmware that's running to
    // appear on each upload.
    delay(2000);

    Serial.println();
    Serial.println("Running Firmware.");

    // Connect to Wifi.
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting...");

    while (WiFi.status() != WL_CONNECTED) {
      // Check to see if connecting failed.
      // This is due to incorrect credentials
      if (WiFi.status() == WL_CONNECT_FAILED) {
        Serial.println("Failed to connect to WIFI. Please verify credentials: ");
        Serial.println();
        Serial.print("SSID: ");
        Serial.println(WIFI_SSID);
        Serial.print("Password: ");
        Serial.println(WIFI_PASS);
        Serial.println();
      }
      delay(5000);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Hello World, I'm connected to the internets!!");
}

void loop()
{
    delay(5000);
    Serial.println("Hello World");
}


// #include <Arduino.h>
// #define LED_PIN   2

// const char *wifi_ssid = "SSID";
// const char *wifi_key = "Password";

// void setup() {
  
//   // put your setup code here, to run once:
//   WiFi.begin(wifi_ssid, wifi_key);
//   Serial.begin(115200);
//   delay(100);
//   Serial.println("%s - run");
//   pinMode(LED_PIN, OUTPUT);
//   Serial.println("hello,yukai");
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   Serial.println("hello,yukai");
//   delay(300);
//   digitalWrite(LED_PIN, HIGH);
//   delay(1000);
//   digitalWrite(LED_PIN, LOW);
//   delay(1000);
// }

