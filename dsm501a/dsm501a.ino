#include <Arduino.h>
#include <string.h>

byte buff[2];
int pin = 18;//DSM501A input D8
unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
 
int i=0;
void setup(){
    Serial.begin(115200);
    pinMode(18,INPUT);
    //starttime = millis(); 
}
void loop(){
/*
    duration = pulseIn(pin, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();
    if ((endtime-starttime) > sampletime_ms){
        ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
        Serial.print("lowpulseoccupancy: ");
        Serial.println(lowpulseoccupancy);
        Serial.print("ratio: ");
        Serial.println(ratio);
        Serial.print("DSM501A: ");
        Serial.println(concentration);
        Serial.print(";\n\n");
    
        lowpulseoccupancy = 0;
        starttime = millis();
    }
*/  
    long concentration = getPM(18);
    Serial.print("Concentração: ");
    Serial.println(concentration);
}

long getPM(int DUST_SENSOR_DIGITAL_PIN) {
    starttime = millis();
    while (1) {
        duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
        lowpulseoccupancy += duration;
        endtime = millis();
        
        if ((endtime-starttime) >= sampletime_ms) {
            ratio = lowpulseoccupancy / (sampletime_ms*10.0);
            //ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100 -> Not working
            long concentration = 1.1 * pow( ratio, 3) - 3.8 *pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
            Serial.println(ratio);
            lowpulseoccupancy = 0;
            return(concentration);    
        }
    }  
}