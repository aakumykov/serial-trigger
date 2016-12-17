#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

SerialListener sListener;
Interval interval(10);
CommandParser cmdParser;

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

      for (int i=0; i<len; i++) { Serial.print(data[i]); }
      Serial.println("");

//      Serial.print(data);
//      Serial.print(" (");
//      Serial.print(len);
//      Serial.print(")");
//      Serial.print("");
//      Serial.println("");

//      Serial.println("------ main program ------");
//      for (int i=0; i<len; i++) {
//        Serial.print(i); Serial.print(": ");
//        Serial.print(data[i]);
//        Serial.print(" [code: "); Serial.print(byte(data[i])); Serial.print("]");
//        Serial.println("");
//      }
//      Serial.println("------ main program ------");
    }
  }
}

