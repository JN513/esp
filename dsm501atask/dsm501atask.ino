#include <Arduino.h>
#include <string.h>

TaskHandle_t Task1;

byte buff[2];
int pin = 18; //DSM501A input D8

unsigned long duration;
unsigned long starttime;
unsigned long endtime;

unsigned long sampletime_ms     = 30000;
unsigned long lowpulseoccupancy = 0;

float ratio                     = 0;
float concentration             = 0;

void setup(){
    Serial.begin(115200);
    xTaskCreatePinnedToCore(
        Tarefa_1, // Function to implement the task
        "Task1", // Name of the task
        10000,  // Stack size in words
        NULL,  // Task input parameter
        10,  // Priority of the task
        &Task1,  // Task handle.
        1 // Core where the task should run
    );
    delay(500); 
    pinMode(18, INPUT);
    starttime = millis();
}

void Tarefa_1( void * pvParameters ){
    for(;;){
        duration = pulseIn(pin, LOW);
        lowpulseoccupancy += duration;
        endtime = millis();
        if ((endtime - starttime) > sampletime_ms){
            ratio = (lowpulseoccupancy - endtime + starttime + sampletime_ms) / (sampletime_ms * 10.0); // Integer percentage 0=>100
            concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;             // using spec sheet curve
            Serial.print("lowpulseoccupancy:");
            Serial.print(lowpulseoccupancy);
            Serial.print("\n");
            Serial.print("ratio:");
            Serial.print("\n");
            Serial.println(ratio);
            Serial.print("DSM501A:");
            Serial.println(concentration);
            Serial.print(";\n\n");

            lowpulseoccupancy = 0;
            starttime = millis();
        }
    }
}

void loop(){

}
