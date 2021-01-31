#include <Ultrasonic.h>
#include <Arduino.h>
#include <analogWrite.h> 
//conexão dos pinos para o sensor ultrasonico
#define PORTA_TRIGGER   35
#define PORTA_ECHO      34
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic1(PORTA_TRIGGER, PORTA_ECHO);
// declarar variável distancia do tipo inteiro sem sinal
 
void setup(){
    // Inicializa
    Serial.begin(115200);
}
 
 
void loop()
{
    Serial.print(ultrasonic1.read()); // Prints the distance on the default unit (centimeters)
    Serial.println("cm");
    delay(500);
}