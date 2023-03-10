#include <Arduino.h>
#include"esp32-hal-ledc.h"

const int ledPin = 19;
int servoMaxPWM;
int servoMinPWM;

void setup() {
  // 使用するタイマーのチャネルと周波数を設定
  //freqの設定　sg90は20ms(0.02秒)のパルス幅→1/0.02=50→ 50(freq)
  // ledcSetup(0, 50, 8);//channel, freq, bit
  Serial.begin(9600);
  ledcSetup(0,50,16);
  ledcAttachPin(ledPin, 0);//出力pin, channel
  int resolution = 65535;
  float minpulus = 0.56;
  float maxpulus = 2.4;
  float basepulus = 20;
  servoMinPWM = int(resolution * (minpulus/basepulus));
  servoMaxPWM = int(resolution * (maxpulus/basepulus));
  int servoMeanPWM = (servoMaxPWM+servoMinPWM)/2;
  ledcWrite(0,int(servoMeanPWM));
  delay(500);


} 
void loop() {
  
  for(int i = servoMinPWM; i <servoMaxPWM; i+=100){
    ledcWrite(0,i);
    delay(50);
  }
  for(int i = servoMaxPWM; i > servoMinPWM; i-=100){
    ledcWrite(0,i);
    delay(50);
  }
}