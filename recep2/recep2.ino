#include <Arduino.h>
#define LEDPIN 27
//you may increase this value on Arduinos with greater than 2k SRAM
#define maxLen 650
 
volatile  unsigned int irBuffer[maxLen]; //stores timings - volatile because changed by ISR
volatile unsigned int x = 0; //Pointer thru irBuffer - volatile because changed by ISR
 
void setup() {
  Serial.begin(115200); //change BAUD rate as required
  attachInterrupt(27, rxIR_Interrupt_Handler, CHANGE);//set up ISR for receiving IR signal
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
  Serial.println(F("Press the button on the remote now - once only"));
  delay(5000); // pause 5 secs
  if (x) { //if a signal is captured
    digitalWrite(LEDPIN, HIGH);//visual indicator that signal received
    Serial.println();
    Serial.print(F("Raw: (")); //dump raw header format - for library
    Serial.print((x - 1));
    Serial.print(F(") "));
    detachInterrupt(0);//stop interrupts & capture until finshed here
    for (int i = 1; i < x; i++) { //now dump the times
      //if (!(i & 0x1)) Serial.print(F("-"));  //comentar aqui aparentemente remove o sinal negativo do nmrs do array!!
      Serial.print(irBuffer[i] - irBuffer[i - 1]);
      Serial.print(F(", "));
    }
    x = 0;
    Serial.println();
    Serial.println();
    digitalWrite(LEDPIN, LOW);//end of visual indicator, for this time
    attachInterrupt(27, rxIR_Interrupt_Handler, CHANGE);//re-enable ISR for receiving IR signal
  }
 
}
 
void rxIR_Interrupt_Handler() {
  if (x > maxLen) return; //ignore if irBuffer is already full
  irBuffer[x++] = micros(); //just continually record the time-stamp of signal transitions
 
}
;//Raw: (135) 4564, 4452, 607, 1632, 608, 1633, 607, 1633, 607, 512, 608, 511, 609, 513, 607, 513, 608, 512, 608, 1632, 607, 1632, 608, 1632, 608, 513, 606, 514, 607, 513, 608, 512, 608, 513, 606, 1634, 607, 1632, 607, 1633, 607, 513, 607, 513, 607, 513, 608, 512, 608, 513, 607, 514, 606, 514, 607, 513, 607, 1633, 607, 1633, 607, 1632, 607, 1633, 607, 1631, 609, 46754, 4563, 4453, 606, 1633, 607, 1633, 607, 1632, 606, 515, 607, 513, 607, 512, 608, 513, 607, 514, 606, 1633, 607, 1633, 607, 1633, 606, 514, 607, 514, 606, 514, 605, 515, 606, 514, 606, 1634, 606, 1633, 607, 1633, 607, 513, 606, 514, 606, 514, 606, 514, 606, 514, 607, 513, 607, 514, 606, 514, 606, 1633, 607, 1633, 606, 1633, 607, 1633, 607, 1633, 607