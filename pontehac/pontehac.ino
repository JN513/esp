#include <analogWrite.h>
#include "Arduino.h"

// Definindo pinos do NodeMcu para driver Ponte H
// Pinos de controle motor A
int IN1 = 12;
int IN2 = 14;
// Pinos de controle motor B
int IN3 = 27;
int IN4 = 26;

const int freq = 1000;
const int resolution = 12;

void setup(){
    //Define os pinos como saida
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    ledcSetup(0, freq, resolution);
    ledcSetup(1, freq, resolution);
    ledcSetup(2, freq, resolution);
    ledcSetup(3, freq, resolution);

    ledcAttachPin(IN1, 0);
    ledcAttachPin(IN2, 1);
    ledcAttachPin(IN3, 2);
    ledcAttachPin(IN4, 3);

}
 
void loop(){
        //Para o motor A
    ledcWrite(2, 4094);
    ledcWrite(3, 4094);
    delay(500);//aguarda 500 ms

    ledcWrite(2, 0);
    ledcWrite(3 , 4094);

    delay(5000);

    ledcWrite(2, 4094);
    ledcWrite(3, 4094);
    delay(500);//aguarda 500 ms

    ledcWrite(3, 0);
    ledcWrite(2 , 4094);

    delay(5000);
}