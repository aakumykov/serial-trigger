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

//      int len = sListener.length();
//      char* data = sListener.data();

      Serial.print("length: "); Serial.println(sListener.length());
      Serial.print("length: "); Serial.println(sListener.length());
      Serial.print("data: "); Serial.println(sListener.data());
      Serial.print("length: "); Serial.println(sListener.length());
      Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
  }
}

