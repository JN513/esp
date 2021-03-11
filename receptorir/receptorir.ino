#include <IRremote.h>
 
IRrecv receptor(27);
 
decode_results resultado;
 
void setup(){
    Serial.begin(115200);
    Serial.println("Iniciando IR");
    receptor.enableIRIn(); 
}
void loop(){
    if (receptor.decode(&resultado)) {
        Serial.print(resultado.value);
        Serial.print(" ");
        Serial.println(resultado.value, HEX);
        receptor.resume(); 
    }
    delay(100);
}