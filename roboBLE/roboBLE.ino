#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Motors.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Definindo pinos do NodeMcu para driver Ponte H
// Pinos de controle motor A
const int IN1 = 12;
const int IN2 = 14;
// Pinos de controle motor B
const int IN3 = 27;
const int IN4 = 26;

Motors Robo(IN1, IN2, IN3, IN4, 4095, 1000, 12, 0, 1, 2, 3);

char key, previouskey = ' ';

void move(char carc){
    if((carc >= '0' and carc <= '9') or (carc >= 'a' or carc <= 'h')){
        key = carc;
        if(previouskey != key){
            switch (key){
                case '0':
                    Serial.println("Stop");
                    Robo.stop();
                    break;

                case '1':
                    Serial.println("Front");
                    Robo.front();
                    break;

                case '2':
                    Serial.println("Behind");
                    Robo.behind();
                    break;

                case '3':
                    Serial.println("Neutral");
                    Robo.neutral();
                    break;

                case '4':
                    Serial.println("Giro A");
                    Robo.front_ma();
                    Robo.behind_mb();
                    break;

                case '5':
                    Serial.println("Giro B");
                    Robo.front_mb();
                    Robo.behind_ma();
                    break;

                case '6':
                    Serial.println("A giro B");
                    Robo.front_ma();
                    Robo.stop_mb();
                    break;

                case '7':
                    Serial.println("B giro A");
                    Robo.front_mb();
                    Robo.stop_ma();
                    break;

                case '8':
                    Serial.println("A giro B reverso");
                    Robo.behind_ma();
                    Robo.stop_mb();
                    break;

                case '9':
                    Serial.println("B giro A reverso");
                    Robo.behind_mb();
                    Robo.stop_ma();
                    break;

                case 'a':
                    Serial.println("Front A");
                    Robo.front_ma();
                    break;
                
                case 'b':
                    Serial.println("Front B");
                    Robo.front_mb();
                    break;

                case 'c':
                    Serial.println("Behind A");
                    Robo.behind_ma();
                    break;

                case 'd':
                    Serial.println("Behind B");
                    Robo.behind_mb();
                    break;

                case 'e':
                    Serial.println("Stop A");
                    Robo.stop_ma();
                    break;

                case 'f':
                    Serial.println("Stop B");
                    Robo.stop_mb();
                    break;

                case 'g':
                    Serial.println("Neutral A");
                    Robo.neutral_ma();
                    break;

                case 'h':
                    Serial.println("Neutral B");
                    Robo.neutral_mb();
                    break;

            }

            previouskey = key;
        }
    }
}

class Callbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();

        if (value.length() > 0) {
            Serial.println("*********");
            Serial.print("New value: ");
            for (int i = 0; i < value.length(); i++)
                Serial.print(value[i]);

            Serial.println();
            Serial.println("*********");

            for (int i = 0; i < value.length(); i++) move(value[i]);
        }
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("The device started, now you can pair it with bluetooth!");

    BLEDevice::init("Robo");
    BLEServer *pServer = BLEDevice::createServer();

    BLEService *pService = pServer->createService(SERVICE_UUID);

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                            CHARACTERISTIC_UUID,
                                            BLECharacteristic::PROPERTY_READ |
                                            BLECharacteristic::PROPERTY_WRITE
                                        );

    pCharacteristic->setCallbacks(new Callbacks());

    pCharacteristic->setValue("Hello World");
    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
}

void loop() {

    delay(2000);
}