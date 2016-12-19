#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

SerialListener sListener(512, ';');
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
      //int len = sListener.length();
      //char* data = sListener.data();

      //Serial.println("");
      //Serial.print("length: "); Serial.println(len);

//      Serial.println("------ main program ------");
//      for (int i=0; i<len; i++) {
//        Serial.print(i); Serial.print(": ");
//        Serial.print(data[i]);
//        Serial.print(" [code: "); Serial.print(byte(data[i])); Serial.print("]");
//        Serial.println("");
//      }      
//      Serial.println("------ main program ------");

//        cmdParser.parse(data);
//        Serial.println(cmdParser.command());
    }
  }
}

