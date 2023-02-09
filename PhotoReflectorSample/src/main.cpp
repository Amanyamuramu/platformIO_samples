#include <Arduino.h>

const int cds_pin = 25;


void setup() {
  Serial.begin(9600);
  pinMode(cds_pin,INPUT);
}

void loop(){
  int cds_data = analogRead(cds_pin);
  Serial.println("cds_value:/=");
  Serial.println(cds_data);
  delay(500);
}