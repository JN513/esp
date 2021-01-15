//inclusão de algumas bibliotecas
#include <SPI.h>
#include <MFRC522.h>
 
// Definiremos o id que será liberado o acesso
#define ID "09 F7 30 31"
 
//define alguns pinos do esp32 que serao conectados aos modulos e componentes
#define LedVerde 26
#define LedVermelho 12
#define tranca 2
#define buzzer 15
#define SS_PIN 5
#define RST_PIN 36
 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // define os pinos de controle do modulo de leitura de cartoes RFID

void setup(){
    SPI.begin();   // inicia a comunicacao SPI que sera usada para comunicacao com o mudulo RFID
    
    mfrc522.PCD_Init();  //inicia o modulo RFID
    
    Serial.begin(115200);  // inicia a comunicacao serial com o computador na velocidade de 115200 baud rate
    
    Serial.println("RFID + ESP32");
    Serial.println("Aguardando tag RFID para verificar o id da mesma.");

}

void loop() {
 
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;                 // se nao tiver um cartao para ser lido recomeça o void loop
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;                  //se nao conseguir ler o cartao recomeça o void loop tambem
    }
    
    String conteudo = "";      // cria uma string
    
    Serial.print("id da tag :"); //imprime na serial o id do cartao
    
    for (byte i = 0; i < mfrc522.uid.size; i++){       // faz uma verificacao dos bits da memoria do cartao
        //ambos comandos abaixo vão concatenar as informacoes do cartao...
        //porem os 2 primeiros irao mostrar na serial e os 2 ultimos guardarao os valores na string de conteudo para fazer as verificacoes
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    conteudo.toUpperCase();                      // deixa as letras da string todas maiusculas
    
    if (conteudo.substring(1) == ID){ // verifica se o ID do cartao lido tem o mesmo ID do cartao que queremos liberar o acesso
        Serial.println("acesso concedido");
    }
}
