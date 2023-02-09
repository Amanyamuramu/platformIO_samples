#include <Arduino.h>
#include"esp32-hal-ledc.h"

const int FSR_PIN = 34;
const int SERVO_PIN = 19;

int sensorValue = 0;
int oldsensorValue = 0;
//samplingの間隔は2msかそれいじょうのほうが望ましい？

const int samplingNum = 25; //20msくらい開けておく
const float samplingTime = 3;//sampling数

//移動平均をかけるための変数
const int stock_rotation_term = 10;//移動平均の期間（標本数）
int stock_rotation_number = 0;
int stock_data[stock_rotation_term];
int new_data;

//移動平均用関数
int moving_average(int data) {

  if (stock_rotation_number > stock_rotation_term) {
    stock_rotation_number = 0;
  }
  stock_rotation_number++;

  stock_data[stock_rotation_number] = data;
  int result=0;

  for (int i = 0; i < stock_rotation_term; i++) {
    result += stock_data[i];
  }

  result = result/stock_rotation_term;
  return result;
}

//センサの値を別coreで取得
void subProcess(void * pvParameters) {
    while (1) {
        // 10点平均化
        int sum = 0; 
        for(int i = 0; i < samplingNum; i++){
          sum += analogRead(FSR_PIN);
          delay(samplingTime);
        }
        sensorValue = sum/samplingNum;
    }
}
 
void setup() {
    Serial.begin(9600);
    pinMode(FSR_PIN,INPUT);
    ledcSetup(0,50,16);
    ledcAttachPin(SERVO_PIN, 0);//出力pin, channel/
    for(int i = 0; i <stock_rotation_term; i++){
    stock_data[i] = 1835; 
  }
    xTaskCreatePinnedToCore(subProcess, "subProcess", 4096, NULL, 1, NULL, 0); //Core 0でタスク開始
    //subProcess関数を呼び出す

}

//サーボ駆動
void loop() {
  int servoAngle = map(sensorValue,0,4095,3800,1835);
  servoAngle = moving_average(servoAngle);
  ledcWrite(0,servoAngle);
  delay(samplingNum*samplingTime);

  //補完
  // // oldensorvalue　と sensorvalueを比較して平均化→new value 2つのデータ→3つに（）

  //   int middleValue = (oldsensorValue + sensorValue)*0.5;
  //   int oldAngle = map(oldsensorValue,0,4095,3800,1835);
  //   int middleAngle = map(middleValue,0,4095,3800,1835);
  //   oldsensorValue = sensorValue;
  //   // angleに移動平均をかけたものをしよう
  //   oldAngle = moving_average(oldAngle);
  //   //どれくらいの幅
  //   ledcWrite(0,oldAngle);
  //   delay(samplingNum/2 * samplingTime);

  //   middleAngle = moving_average(middleAngle);
  //   ledcWrite(0,middleAngle);
  //   delay(samplingNum/2 * samplingTime);
}