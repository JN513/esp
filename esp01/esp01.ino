#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
}

void loop(){
    Serial.println("Ligado");
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    delay(2000);
    Serial.println("Desligado");
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    delay(2000);
}