#include <Arduino.h>

volatile int intdata = 0;
 
//0 coreで駆動する関数(グローバルなintdataに対して永遠に1000を加算)
void subProcess(void * pvParameters) {
    while (1) {
        intdata = intdata + 1000;
        Serial.println(intdata);
        delay(500);
    }
}
 
void setup() {
    Serial.begin(9600);
    xTaskCreatePinnedToCore(subProcess, "subProcess", 4096, NULL, 1, NULL, 0); //Core 0でタスク開始
    //subProcess関数を呼び出す

}
 
void loop() {
    intdata = intdata + 1;
    Serial.println(intdata);
    delay(500);
}