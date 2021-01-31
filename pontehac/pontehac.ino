#include <analogWrite.h>
#include "Arduino.h"

// Definindo pinos do NodeMcu para driver Ponte H
// Pinos de controle motor A
int IN1 = 12;
int IN2 = 14;
// Pinos de controle motor B
int IN3 = 27;
int IN4 = 26;
 
void setup(){
    //Define os pinos como saida
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}
 
void loop(){
        //Para o motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500);//aguarda 500 ms

    digitalWrite(IN1, LOW);
    for(int i = 0; i < 4095; i++){
        analogWrite(IN2, i);
        delay(10);
    }

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500);//aguarda 500 ms

    digitalWrite(IN2, LOW);
    for(int i = 0; i < 4095; i++){
        analogWrite(IN1, i);
        delay(500);
    }
}