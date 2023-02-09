#include <Arduino.h>
#include"esp32-hal-ledc.h"

#define BUF_LEN 15
// #define SENSOR_PIN 35 

//バッファ
int buf[BUF_LEN];
int indexid = 0; 
//フィルター後の値
int filterVal =0;
const int SERVO_PIN = 19;
const int FSR_PIN = 34;

bool fragment = false;
int old_fsr_data = 0;

void Actuation(int data, int old_data){
  // int angle = map(x,0,4095,1835,8126);
  // int preAngle = map(old_data,0,4095,6945,4980);
  // int servo_angle = map(data,0,4095,6945,4980);
  int preAngle = map(old_data,0,4095,3800,1835);
  int servo_angle = map(data,0,4095,3800,1835);
  int difAngle =  abs(preAngle - servo_angle);
  int delaymillis = difAngle*2.7;
  Serial.println(delaymillis);

  //もし前回の値と今回の値を比較したangleが7.7より低いならバンド幅のみのdelayを与える
  if(difAngle < 8){
    ledcWrite(0,servo_angle);
    delay(delaymillis);//バンド幅
    // delay(4);
    // delay(5);
  }
  //もし前回の値と今回の値を比較したangleが8以上なら（else）なら+8or-8を与える
  else{
    if((servo_angle - preAngle)>0){
      ledcWrite(0,preAngle+8);
    }
    else{
      ledcWrite(0,preAngle-8);
    }
    delay(15);//バンド幅
  }
  // if(difAngle > 35){
  //   //もし35度より大きかった場合、前回の値に固定
  //   if((servo_angle - preAngle)>0){
  //     ledcWrite(0,preAngle+30);
  //   }
  //   else{
  //     ledcWrite(0,preAngle-30);
  //   }
  //   delay(81);
  // }
  // else{
  //   ledcWrite(0,servo_angle);
  //   delay(delaymillis);
  // }
}


void setup() {
  Serial.begin(9600);
  pinMode(FSR_PIN,INPUT);
  ledcSetup(0,50,16);
  ledcAttachPin(SERVO_PIN, 0);//出力pin, channel/

  for(int i=0; i<BUF_LEN; i++) {
    buf[i] = 0;
  }
}

void loop(){
  //analogreadした後計算しない
  int fsr_data = analogRead(FSR_PIN);
  // Actuation(fsr_data,old_fsr_data);
  // old_fsr_data = fsr_data;
  

  buf[indexid] = fsr_data;
  indexid = (indexid+1)%BUF_LEN;
  long sum = 0;
  //フィルタ後の値を計算
  for(int i=0; i<BUF_LEN; i++) {
    sum += buf[i];
  }
  filterVal = sum / BUF_LEN;
  Actuation(filterVal,old_fsr_data);
  old_fsr_data = filterVal;

}