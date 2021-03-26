#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(19, INPUT);
}

void loop(){
    Serial.print("Botao: ");
    Serial.println(digitalRead(19));
    delay(2000);
}