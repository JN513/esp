#include <Arduino.h>
// Projeto Curto Circuito - A4988 & Arduino: Controle para motores Bipolar
//---- Pinos de controle A4988--- 
#define ENA 14 // Enable ativa os drivers do motor
#define MS1 12 // Seleciona a resolução do passo
#define MS2 25 // Seleciona a resolução do passo
#define MS3 26 // Seleciona a resolução do passo 
#define RST 27 // Desativa os drivers de saída
#define SLP 33 // Inicia um descanso para algumas funções do drive
#define STP 32 // Avanço do passo
#define DIR 35 // Direção do passo
//---- Variáveis de controle ----
int PPR = 0;      // pulsos por resolução
int passo = 0;    // passos
int temp = 1000;  // tempo entre os passos 
void setup(){
    pinMode(ENA, OUTPUT);
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);
    pinMode(STP, OUTPUT);
    pinMode(DIR, OUTPUT);
    digitalWrite(SLP, LOW);   // Sleep desabilitado 
    digitalWrite(DIR, HIGH);  // Sentido Horário habilitado
    //digitalWrite(RST, HIGH);  // RST habilitado 
    Serial.begin(115200);
    Serial.println("Pressione: r- para resetar // s - para iniciar Sleep // o - para desativar Sleep");
    delay(100);
    Serial.println("1 para FULL - STEP // 2 para HALF - STEP // 3 para Quarter - STEP // 4 para Eighth - STEP // 5 para Sixteenth - STEP");
    full();
    HR();
}

void loop(){
    //volta();
    digitalWrite(STP, LOW);
    delayMicroseconds(temp); //Tempo em Microseconds
    digitalWrite(STP, HIGH);
    delayMicroseconds(temp);
}
void full(){
  PPR = 200;               // Em Full - 200 passos
  Serial.println("Modo Passo Completo (Full - Step)");
  digitalWrite(MS1, LOW);  
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
}
void volta() {
    //HR();  // Inicia o sentido horário
    while (PPR > passo){      // Enquanto PPR for maior que passo
        // Avança o passo
        digitalWrite(STP, LOW);
        delayMicroseconds(temp); //Tempo em Microseconds
        digitalWrite(STP, HIGH);
        delayMicroseconds(temp);
        passo++; // Aumenta em 1 o valor de passo
    }
    passo = 0; // valor de passso muda pra 0 
    //ena2();    
    //delay(1000);
    //ena();
    /*
    AH();      // Inicia o Sentido Anti-horário
    while (PPR > passo){      // Enquanto PPR for maior que passo
            // Avança o passo
        digitalWrite(STP, LOW);
        delayMicroseconds(temp);
        digitalWrite(STP, HIGH);
        delayMicroseconds(temp);
        passo++;
    }
    passo = 0;
    ena2();
    delay(1000);
    ena();*/
}
void ena2() {
    digitalWrite(ENA, HIGH);  // Ativa o A4988
    delay(10);
}
void ena() {
    digitalWrite(ENA, LOW);   // Desativa o A4988
    delay(10);
}
void HR() {                // Sentido Horário
    passo = 0;     
    Serial.println("Sentido - Horario");
    digitalWrite(DIR, HIGH);
}
void AH()  {               // Sentido Anti-Horário 
    passo = 0;
    Serial.println("Sentido - Anti-horario");
    digitalWrite(DIR, LOW);
}