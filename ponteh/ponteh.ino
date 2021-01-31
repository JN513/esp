#include <Arduino.h>
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
    //Gira o Motor A no sentido horario
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(2000); //aguarda 2s
    
    //Para o motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500);//aguarda 500 ms
    
    //Gira o Motor B no sentido horario
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(2000); //aguarda 2s
    
    //Para o motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(500);//aguarda 500 ms

    //Gira o Motor A no sentido anti-horario
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(2000); //aguarda 2s
    
    //Para o motor A
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    delay(500); //aguarda 500 ms
    
    //Gira o Motor B no sentido anti-horario
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(2000);//aguarda 2s
    
    //Para o motor B
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(500); //aguarda 500ms
    analogWrite(IN3, 2000);
}