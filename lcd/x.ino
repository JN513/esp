#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
 lcd.begin();
 lcd.backlight();
 
 lcd.print("ESP32 - Projeto");
 lcd.setCursor(0, 1);
 lcd.print("com display!");
}
 
void loop() {}