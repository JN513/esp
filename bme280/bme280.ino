#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

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

void setup() {
    Serial.begin(115200);
    Serial.println(F("BME280 test"));

    bool status;

    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Default Test --");
    delayTime = 1000;
    Serial.println();

    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    display_init();

    /* Print message telling to wait */
    display.clearDisplay();    
    display.setCursor(0, OLED_LINE1);
    display.print("Aguarde...");
    display.display();
}

void loop() { 
    printValues();
    delay(delayTime);
}

void printValues() {    
    // Convert temperature to Fahrenheit
    /*Serial.print("Temperature = ");
    Serial.print(1.8 * bme.readTemperature() + 32);
    Serial.println(" *F");*/
    
    double temp = bme.readTemperature();
    double pres = bme.readPressure() / 100.0F;
    double alti = bme.readAltitude(SEALEVELPRESSURE_HPA);
    double humi = bme.readHumidity();

    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(pres);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(alti);
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(humi);
    Serial.println(" %");


    display.clearDisplay();   
    display.setCursor(0, OLED_LINE1);
    display.print("Temperature = ");
    display.print(temp);
    display.println(" *C");
    display.setCursor(0, OLED_LINE2);
    display.print("Pressure = ");
    display.setCursor(0, OLED_LINE3);
    display.print(pres);
    display.println(" hPa");
    display.setCursor(0, OLED_LINE4);
    display.print("Approx. Altitude = ");
    display.setCursor(0, OLED_LINE5);
    display.print(alti);
    display.println(" m");
    display.setCursor(0, OLED_LINE6);
    display.print("Humidity = ");
    display.print(humi);
    display.println(" %");
    display.display(); 

    Serial.println();
}