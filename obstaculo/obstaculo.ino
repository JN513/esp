#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(27, INPUT);
}

void loop(){
    Serial.print("obstaculo: ");
    Serial.println(digitalRead(27));
    delay(2000);
}