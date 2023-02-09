// #include "esp_system.h"
#include <Arduino.h>
#include <ESP32Servo.h>

const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 5000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;
unsigned long oldTime = 0;
bool flagofsample = true;

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#define OnB_LED 2

bool fragLED = false;

Servo servo;
const int servo_pin  = 12;
const int cds_pin = 35;
const int dac_max = 4096;


void IRAM_ATTR resetModule() {
  fragLED = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(OnB_LED, OUTPUT);
  servo.attach(servo_pin);
  pinMode(cds_pin,INPUT);
  //enable interrupt
}
 
void loop() {
  if(flagofsample){
    delay(2000);
    flagofsample = false;

    timer = timerBegin(0, 80, true);                  //timer 0, div 80
    timerAttachInterrupt(timer, &resetModule, true);  //attach callback
    timerAlarmWrite(timer, wdtTimeout * 1000, true); //set time in us     
    timerAlarmEnable(timer);
  }
  if(fragLED){ 
    timerWrite(timer, 0);
    Serial.println("Im interrupted");
    int cds_data = analogRead(cds_pin);
    Serial.println(cds_data);
    servo.write(70);
    delay(1000);
    servo.write(90);
    delay(1000);
    fragLED = false;
  }
  // long loopTime = millis();
  Serial.println("hello");
  delay(500);
}
