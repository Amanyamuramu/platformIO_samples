// #include "esp_system.h"
#include <Arduino.h>
#include <ESP32Servo.h>

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#define OnB_LED 2

Servo servo;
const int servo_pin  = 18;
const int cds_pin = 35;
int angle;

void setup() {
  Serial.begin(9600);
  pinMode(OnB_LED, OUTPUT);
  servo.attach(servo_pin);
  pinMode(cds_pin,INPUT);
  //enable interrupt
}
 
void loop() {
  // int cds_data = analogRead(cds_pin);
  // Serial.println("cds_value:/=");
  // Serial.println(cds_data);
  // int angle;
  // angle = map(cds_data, 0,4096,0,179);
  // Serial.println("angle:/=");
  // Serial.println(angle);
  // servo.write(angle);
  servo.write(60);
  delay(1000);
  servo.write(50);
  delay(1000);
}
