#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

LiquidCrystal_PCF8574 lcd(0x27);
SerialListener sListener;
Interval interval(10);
CommandParser cmdParser;


void show(char* str, int len = NULL) {
  if (NULL != len) {
    for (int i=0; i<len; i++) { Serial.print(str[i]); }
  } else {
    int i = 0;
    char b = str[i];
    while (NULL != b) {
      Serial.print(b);
      char b = str[i++];
    }
  }
  Serial.println("");
}

void lcdShow(char* msg, int row) {
  lcd.setCursor(0,row);
  lcd.print("                ");
  lcd.setCursor(0,row);
  lcd.print(msg);
}


void setup() {
  char greeting[] = "=serial-trigger=";
  
  Serial.begin(9600);
  Serial.println(greeting);

  lcd.begin(16,2); lcd.setBacklight(1); lcd.clear(); lcd.home();
  lcdShow(greeting,0);

  delay(500);
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.recieved()){
      
      //int len = sListener.length();
      char* data = sListener.data();
      delay(3000);
      
    }
  }
}

