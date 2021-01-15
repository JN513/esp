#include <Ultrasonic.h>
#include <Arduino.h>
//conexão dos pinos para o sensor ultrasonico
#define PORTA_TRIGGER   GPIO_NUM_35
#define PORTA_ECHO      GPIO_NUM_34
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(PORTA_TRIGGER, PORTA_ECHO);
// declarar variável distancia do tipo inteiro sem sinal
float distancia;
 
void setup(){
    // Inicializa
    Serial.begin(115200);
}
 
 
void loop(){
    // realiza a leitura da distancia
    ultrasonic.measure();
    distancia = ultrasonic.get_cm();
    Serial.println("Leitura do Sensor de Distancia em cm:");
    Serial.println(distancia);
    delay(500);
}