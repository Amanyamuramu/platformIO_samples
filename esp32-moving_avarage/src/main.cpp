#include <Arduino.h>

const int FSR_PIN = 34;

const int stock_rotation_term = 10;//移動平均の期間（標本数）
int stock_rotation_number = 0;//輪番用のカウント
int stock_data[stock_rotation_term];//データをストックする配列
int new_data;//センサから取得した最新のデータ

int moving_average(int data) {//移動平均値の取得

  if (stock_rotation_number > stock_rotation_term) {
    stock_rotation_number = 0;
  }
  stock_rotation_number++;

  stock_data[stock_rotation_number] = data;//ストックの輪番箇所にデータ上書き
  int result=0;//結果を初期化

  for (int i = 0; i < stock_rotation_term; i++) {//ストックした値を合計する
    result += stock_data[i];
  }

  result = result/stock_rotation_term; //合計値を標本数でを割る
  return result;
}

void setup() {
  Serial.begin(9600);
  pinMode(FSR_PIN,INPUT);
  for(int i = 0; i <stock_rotation_term; i++){
    stock_data[i] = 0; 
  }
}

void loop(){
  new_data = analogRead(FSR_PIN);
  int watchingdata = moving_average(new_data);
  Serial.print("nothing value");
  Serial.println(new_data);
  Serial.print("avg M value");
  Serial.println(watchingdata);

}