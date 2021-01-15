#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(27, INPUT);
}

void loop(){
    Serial.print("Luz: ");
    Serial.println(analogRead(27));
    delay(2000);
}