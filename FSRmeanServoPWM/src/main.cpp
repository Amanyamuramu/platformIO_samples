#include <Arduino.h>
#include"esp32-hal-ledc.h"

//フィルタリングで使用する値：
#define BUF_LEN 15
int buf[BUF_LEN];
int indexid = 0; 
//フィルター後の値
int filterVal =0;

const int SERVO_PIN = 19;
const int FSR_PIN = 34;

bool fragment = false;
int old_fsr_data = 0;

const int sampleSize = 500;
const int groupSize = 5;
const int newDataSize = sampleSize/groupSize;

void Actuation(int data, int old_data){
  int preAngle = map(old_data,0,4095,3800,1835);
  int servo_angle = map(data,0,4095,3800,1835);
  int difAngle =  abs(preAngle - servo_angle);
  int delaymillis = difAngle*2.7;
  Serial.println(delaymillis);
  
  if(difAngle < 7){
    ledcWrite(0,servo_angle);
    // delay(21);//バンド幅
    // delay(4);
    delay(delaymillis);
  }
  
  else{
    if((servo_angle - preAngle)>0){
      ledcWrite(0,preAngle+7);
    }
    else{
      ledcWrite(0,preAngle-7);
    }
    delay(20);
  }
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

  // int fsr_data = analogRead(FSR_PIN);
  // buf[indexid] = fsr_data;
  // indexid = (indexid+1)%BUF_LEN;
  // long sum = 0;

  // //フィルタ後の値を計算
  // for(int i=0; i<BUF_LEN; i++) {
  //   sum += buf[i];
  // }

  // filterVal = sum / BUF_LEN;
  // Actuation(filterVal,old_fsr_data);
  // old_fsr_data = filterVal;

  //10点　平均化のコードを記述：10個とったら平均化、10個とったら平均化
  // 500個→50個：
  int sensorData[sampleSize];
  int newData[newDataSize];
  for(int i = 0; i<sampleSize; i++){
    sensorData[i] = analogRead(FSR_PIN);
    delay(1);
  }
  Serial.println("new sensor data");
  for(int i = 0; i < newDataSize; i++) {
    int sum = 0;
    //データを10個ごとに平均化する
    for(int j = 0; j < groupSize; j++) {
      sum += sensorData[i*groupSize + j];
    }
    newData[i] = sum/groupSize;
    //
    // Serial.println(newData[i]);

    //Actuation
   }
   for(int i = 0; i < newDataSize; i++){
    Actuation(newData[i],old_fsr_data);
    old_fsr_data = newData[i];
    // int angle = map(newData[i],0,4095,3800,1835);
    // Serial.println(angle);
    // ledcWrite(0,preAngle);
    // delay(1);
    
   }
}