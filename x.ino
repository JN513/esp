#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Variaveis Globais
char st[20];
int bat, tempBat, bat2, tempbat2, KM, timet, tempAB, tempM, tempC, rlm, rmC, acess = 0;
/*
Voltagem Bateria = bat
temperatura bateria  = tempBat
Voltagem Bateria (parte eletronica) = bat2 
Temepratura bateria2 (parte eletronica) = tempBat2
Km/h = KM  
Hora de utilização = timet
Temperatura ambiente = tempAb
Temperatura motor = tempM
Temperatura controladora = tempC
Rele (deliga bateria motor ) =rlM
Rele (desliga bateria da controladora) = rlC
Acesso = acess

*/
void setup()
{ //LCD
    Serial.begin(9600);
    lcd.init();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("----Bloqueado----");
    lcd.setCursor(0, 1);
    lcd.print("Aproxime A Tag");
    //NFC
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Aproxime o seu cartao/TAG do leitor");
    Serial.println();
    //declaraçao portas usadas para ligar rele
    pinMode(3, OUTPUT);
}

void loop()
{
    
    //-------------------------------------------------Leitura do DA tag nfc-----------------------------------------------------
    // Busca novos cartões
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        digitalWrite(3, HIGH); // tag na opresente desliga rele da bateria da controladora
        
        return;
    }
    // Seleciona um catão a ser lido
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    //Mostra ID na serial
    //Serial.print("ID da tag: ");
    String conteudo = "";
    byte letra;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       // Serial.print(mfrc522.uid.uidByte[i], HEX);
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
   // Serial.print("Mensagem : ");
    conteudo.toUpperCase();
    //-------------------------------------------------fim-----------------------------------------------------
    //compara  se e chave
    if (conteudo.substring(1) == "F7 F7 30 63") //ID CARTÃO
    {
        lcd.clear(); // se sim acesso e = 1
        Serial.println("Acesso autorizado !");
        Serial.println();
        acess = 1;
    }
    else
    { // se nao e = 0
        lcd.clear();
        Serial.println("Acesso Negado !");
        acess = 0;
    }
    // compara se acess =1 se for libera
   if (acess == 1)
   {
       //depois do acesso autorizado inicia o codigos dentro do if
       digitalWrite(3, LOW);
       delay(5000);

       

       
      }
   if (acess == 0)
   {
       lcd.clear();
       digitalWrite(3, HING);
       lcd.setCursor(0, 0);
       lcd.print("Acesso Negado!");
      
   }

   Serial.println();

   delay(500);
}