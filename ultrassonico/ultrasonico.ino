#include <Arduino.h>

const int trigPin = 4;
const int echoPin = 5;

long duration;
int distance;

void setup(){
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    // Inicializa
    Serial.begin(115200);
}
 
 
void loop(){
    distance = calculateDistance();
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(".");

    delay(2000);
}

int calculateDistance(){   
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    // Define o trigPin no estado HIGH por 10 micro segundos
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // Lê o echoPin, retorna o tempo de viagem da onda sonora em microssegundos
    distance= duration*0.034/2;
    return distance;
}