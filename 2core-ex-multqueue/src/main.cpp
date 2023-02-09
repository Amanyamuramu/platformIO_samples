#include <Arduino.h>

TaskHandle_t thp[2];//マルチスレッドのタスクハンドル格納用
QueueHandle_t xQueue_1;//Queueを使う準備 [キューハンドル名]//Queueの数は不明

//平均化のための配列50個
//線形保管のための配列2個
//preValue, nowValue
//500個数のdata格納用の配列


void Core1a(void *args) {//スレッド ①
  int a = 0;//送信データの変数 : analogreadに変更
  //
  while (1) {
    xQueueSend( xQueue_1, &a, 0 );
    //xQueueSend([キューハンドル名], [送る値], [待ち行列の席が空くまで待つ時間:0待たない]);
    a++;
    delay(1);//次のキュー送信までの時間
  }
}

//センサ用
void Core0a(void *args) {//スレッド ②
  int b = 0;//データ受信用の変数
  while (1) {
    /* メッセージ受信待ち */
    //先頭から50個のデータを表現入れる
    xQueueReceive( xQueue_1, &b, portMAX_DELAY );
    //xQueueSend([キューハンドル名], [データを受信するアドレス], [キュー空きを待つ最大時間。portMAX_DELAYで永久待ち])
    delay(0.5);
  }
}


void setup() {
  Serial.begin(9600);

  xQueue_1 = xQueueCreate( 10, 16 );
  //xQueueCreate( [待ち行列の席数], [一席あたりのバイト数] );　//queueは待たれることを前提に設計→待てるような余白を開けておく

  //スレッドの準備
  xTaskCreatePinnedToCore(Core0a, "Core0a", 4096, NULL, 2, &thp[0], 0);
  xTaskCreatePinnedToCore(Core1a, "Core1a", 4096, NULL, 1, &thp[1], 1);
  //xTaskCreatePinnedToCore(
  //   [タスク名], "[タスク名]", 
  //   [スタックメモリサイズ(4096or8192)], [NULL], 
  //   [タスク優先順位(1-24)] 大きいほど優先順位が高い,
  //   [宣言したタスクハンドルのポインタ(&thp[0])], [CoreID(0or1)]); 
}

void loop() {//メインループ
  Serial.println("[ main ] loop");
  delay(100);
}

