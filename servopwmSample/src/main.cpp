#include <Arduino.h>
#include"esp32-hal-ledc.h"

const int ledPin = 18;
const int maxvalue = 8126;
const int minvalue = 1835;
const int diffvalue = 10;//(一度が21くらいなので)

//(560,1520,2480)microsec
//一定周期のパルス幅は別に4~50の間ならどれでも良い

//これを関数化してとある電圧（0~4096の電圧が来た時に角度にマッピングするようにする）
//value(0~4095)を受け取る
//これを(1835~8126にマッピング)
//servo motorを駆動させる
//delay(一旦は1000とか？)

//servoをもっと滑らかに制御する方法？
//
void Actuation(int x){
  int preAngle;
  int nowAngle;
  int angle = map(x,0,4095,1835,8126);
  ledcWrite(0,angle);
  delay(30);
}

void setup() {
  // 使用するタイマーのチャネルと周波数を設定
  //freqの設定　sg90は20ms(0.02秒)のパルス幅→1/0.02=50→ 50(freq)
  // ledcSetup(0, 50, 8);//channel, freq, bit
  ledcSetup(0,50,16);
  ledcAttachPin(ledPin, 0);//出力pin, channel
} 
void loop() {
  for(int i = 0; i < 4096; i+=10){
    Actuation(i);
    delay(50);
  }
  for(int i = 4096; i > 0; i-=10){
    Actuation(i);
    delay(50);
  }
  //( 0度)
  //x = pwm値//制御パルス幅を上で設定した値で入力
  //50Hz、8bitで1ms幅とするには 1[ms] / {(1/50*1000)[ms] / 2^8[bit]} = 13[bit] 
  //                                    1(ms)   /   20ms   *  255
  //もしsg90で計算して26(0度数)、123(180度数)なら？
  //sg 90 
  //int min = 26;  // (26/1024)*20ms ≒ 0.5 ms  (-90°)→0 .5.6
  //int max = 123; // (123/1024)*20ms ≒ 2.4 ms (+90°) →10bitの時→ 2.4

  //16bit 分解能→65535

  //→duty比を出してそれを計算する
  // 必要な microsec/20msecに対してどれくらいの比率？

  // 
}