#include <IRremote.h>
IRsend irsend; // ligar led IR no pino 3 do arduino
 
int khz = 38; // 38kHz freq do protocolo NEC
int incomingByte = 0; // variável para o dado recebido
 
//insira neste vetor o seus dados do retirados do primeiro sketch que le o codigo IR da tecla que voce escolheu.
unsigned int meuSinalIR[] = {4564, 4452, 607, 1632, 608, 1633, 607, 1633, 607, 512, 608, 511, 609, 513, 607, 513, 608, 512, 608, 1632, 607, 1632, 608, 1632, 608, 513, 606, 514, 607, 513, 608, 512, 608, 513, 606, 1634, 607, 1632, 607, 1633, 607, 513, 607, 513, 607, 513, 608, 512, 608, 513, 607, 514, 606, 514, 607, 513, 607, 1633, 607, 1633, 607, 1632, 607, 1633, 607, 1631, 609, 46754, 4563, 4453, 606, 1633, 607, 1633, 607, 1632, 606, 515, 607, 513, 607, 512, 608, 513, 607, 514, 606, 1633, 607, 1633, 607, 1633, 606, 514, 607, 514, 606, 514, 605, 515, 606, 514, 606, 1634, 606, 1633, 607, 1633, 607, 513, 606, 514, 606, 514, 606, 514, 606, 514, 607, 513, 607, 514, 606, 514, 606, 1633, 607, 1633, 606, 1633, 607, 1633, 607, 1633, 607 
};
 
 
 
void setup() {
    Serial.begin(115200); // abre a porta serial, configura a taxa de transferência para 9600 bps
    Serial.print("Digite a letra l para enviar o sinal IR");
}
 
void loop() {
// apenas responde quando dados são recebidos:
    if (Serial.available() > 0) {
        // lê do buffer o dado recebido:
        incomingByte = Serial.read();
    }
   
    if(incomingByte==108) // numero 108 corresponde a letra l
    {
       // responde com o dado recebido:
       Serial.println("Recebi o comando, enviando sinal");
       irsend.sendRaw(meuSinalIR, sizeof(meuSinalIR) / sizeof(meuSinalIR[0]), khz);
    }
    incomingByte=0;
}