#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(0, INPUT);
}

void loop(){
    Serial.print("Linha: ");
    Serial.println(analogRead(0nte ));
    delay(2000);
}