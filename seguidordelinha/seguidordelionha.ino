#include <Arduino.h>
#include <Motors.h>

// Definindo pinos do NodeMcu para driver Ponte H
// Pinos de controle motor A
const int IN1 = 12;
const int IN2 = 14;
// Pinos de controle motor B
const int IN3 = 27;
const int IN4 = 26;

const int S1 = 25;
const int S2 = 33;

int linha1 = 0;
int linha2 = 0;

Motors Robo(IN1, IN2, IN3, IN4, 1500, 1000, 12, 0, 1, 2, 3);

void setup() {
    Serial.begin(115200);

    pinMode(S1, INPUT);
    pinMode(S2, INPUT);

    Robo.stop();
}

void loop() {
    linha1 = analogRead(S1);
    linha2 = analogRead(S1);

    if(linha1 <= 100 and linha2 <= 100){
        Robo.front();
    }

    if(linha1 <= 100 and linha2 > 100){
        Robo.behind_ma();
        Robo.stop_mb();
    }

    if(linha1 > 100 and linha2 <= 100){
        Robo.behind_mb();
        Robo.stop_ma();
    }


    Serial.print("Lado1: ");
    Serial.println(analogRead(S1));

    Serial.print("Lado2: ");
    Serial.println(analogRead(S2));

    delay(2000);
}