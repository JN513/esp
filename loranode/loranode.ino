/*
  LoRa Simple Gateway/Node Exemple

  This code uses InvertIQ function to create a simple Gateway/Node logic.

  Gateway - Sends messages with enableInvertIQ()
          - Receives messages with disableInvertIQ()

  Node    - Sends messages with disableInvertIQ()
          - Receives messages with enableInvertIQ()

  With this arrangement a Gateway never receive messages from another Gateway
  and a Node never receive message from another Node.
  Only Gateway to Node and vice versa.

  This code receives messages and sends a message every second.

  InvertIQ function basically invert the LoRa I and Q signals.

  See the Semtech datasheet, http://www.semtech.com/images/datasheet/sx1276.pdf
  for more on InvertIQ register 0x33.

  created 05 August 2018
  by Luiz H. Cassettari
*/

#include <SPI.h>              // include libraries
#include <Wire.h>
#include <LoRa.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


/* Definicoes para comunicação com radio LoRa */
#define SCK_LORA           5
#define MISO_LORA          19
#define MOSI_LORA          27
#define RESET_PIN_LORA     14
#define SS_PIN_LORA        18
 
#define HIGH_GAIN_LORA     20  /* dBm */
#define BAND               915E6  /* 915MHz de frequencia */

/* Definicoes do OLED */
#define OLED_SDA_PIN    4
#define OLED_SCL_PIN    15
#define SCREEN_WIDTH    128 
#define SCREEN_HEIGHT   64  
#define OLED_ADDR       0x3C 
#define OLED_RESET      16
 
/* Offset de linhas no display OLED */
#define OLED_LINE1     0
#define OLED_LINE2     10
#define OLED_LINE3     20
#define OLED_LINE4     30
#define OLED_LINE5     40
#define OLED_LINE6     50

#define SEALEVELPRESSURE_HPA (1013.25)

/* Variaveis e objetos globais */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme; // I2C

/* Local prototypes */
void display_init(void);
bool init_comunicacao_lora(void);
void onReceive(int packetSize);
void LoRa_rxMode();
void LoRa_txMode();
void LoRa_sendMessage(char *str);
void onTxDone();


void setup() {
    Serial.begin(115200);                   // initialize serial
    
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    display_init();

    /* Print message telling to wait */
    display.clearDisplay();    
    display.setCursor(0, OLED_LINE1);
    display.print("Aguarde...");
    display.display();


    while(init_comunicacao_lora() == false);
}

void loop() {
    //String payload = getData();

    char *payload = "juliopika";
    LoRa_sendMessage(payload);
    delay(8000);
}

/* Funcao: inicializa comunicacao com o display OLED
 * Parametros: nenhnum
 * Retorno: nenhnum
*/ 
void display_init(void){
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("[LoRa Receiver] Falha ao inicializar comunicacao com OLED");        
    }
    else {
        Serial.println("[LoRa Receiver] Comunicacao com OLED inicializada com sucesso");
     
        /* Limpa display e configura tamanho de fonte */
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
    }
}
 
/* Funcao: inicia comunicação com chip LoRa
 * Parametros: nenhum
 * Retorno: true: comunicacao ok
 *          false: falha na comunicacao
*/
bool init_comunicacao_lora(void){

    bool status_init = false;
    Serial.println("[LoRa Receiver] Tentando iniciar comunicacao com o radio LoRa...");
    SPI.begin(SCK_LORA, MISO_LORA, MOSI_LORA, SS_PIN_LORA);
    LoRa.setPins(SS_PIN_LORA, RESET_PIN_LORA, LORA_DEFAULT_DIO0_PIN);
     
    if (!LoRa.begin(BAND)) {
        Serial.println("[LoRa Receiver] Comunicacao com o radio LoRa falhou. Nova tentativa em 1 segundo...");        
        delay(1000);
        status_init = false;
    }
    else{
        /* Configura o ganho do receptor LoRa para 20dBm, o maior ganho possível (visando maior alcance possível) */ 
        LoRa.setTxPower(HIGH_GAIN_LORA); 
        Serial.println("[LoRa Receiver] Comunicacao com o radio LoRa ok");
        Serial.println("LoRa Simple Node");
        Serial.println("Only receive messages from gateways");
        Serial.println("Tx: invertIQ disable");
        Serial.println("Rx: invertIQ enable");
        Serial.println();

        LoRa.onReceive(onReceive);
        LoRa.onTxDone(onTxDone);
        LoRa_rxMode();

        status_init = true;
    }
 
    return status_init;
}

void LoRa_rxMode(){
    LoRa.enableInvertIQ();                // active invert I and Q signals
    LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
    LoRa.idle();                          // set standby mode
    LoRa.disableInvertIQ();               // normal mode
}

void LoRa_sendMessage(char *str) {
    int len = strlen(str);
    LoRa_txMode();                        // set tx mode
    LoRa.beginPacket();                   // start packet
    for(int i = 0; i < len; i++){
        LoRa.write((unsigned char *)str+i, sizeof(str[i]));
    }
    LoRa.endPacket();                 // finish packet and send it
}

void onReceive(int packetSize) {
    String message = "";
    char byte_recebido;
    int lora_rssi = 0;

    if (packetSize) {
        Serial.println("[LoRa Receiver] Há dados a serem lidos");
         
        /* Recebe os dados conforme protocolo */               
        for(int i = 0; i < packetSize; i++); {
            byte_recebido = (char)LoRa.read();
            message += byte_recebido;
        }
 
        Serial.println(message);

        /* Escreve RSSI de recepção e informação recebida */
        lora_rssi = LoRa.packetRssi();
        Serial.printf("RSSI: %d\n", lora_rssi);
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Informacao: ");
        display.setCursor(0, OLED_LINE3);
        display.println(message);
        display.display();      
    }
}

void onTxDone() {
    Serial.println("TxDone");
    LoRa_rxMode();
}

boolean runEvery(unsigned long interval) {
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        return true;
    }
    return false;
}

