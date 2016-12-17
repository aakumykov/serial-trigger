#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

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

void setup() {
  Serial.begin(9600);
  Serial.println("=serial-trigger=");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.recieved()){
      int len = sListener.length();
      char* data = sListener.data();

// Странный эффект при последовательности (пять раз, с нуля):
// command:1,2,3,4,5;

      show(data, len);

// !Эта конструкция выдаёт глючные данные!
//      Serial.print(data);
//      Serial.print(" (");
//      Serial.print(len);
//      Serial.print(")");
//      Serial.print("");
//      Serial.println("");
// !Эта конструкция выдаёт глючные данные!

//      Serial.println("------ main program ------");
//      for (int i=0; i<len; i++) {
//        Serial.print(i); Serial.print(": ");
//        Serial.print(data[i]);
//        Serial.print(" [code: "); Serial.print(byte(data[i])); Serial.print("]");
//        Serial.println("");
//      }
//      Serial.println("------ main program ------");

        cmdParser.parse(data);
    }
  }
}

