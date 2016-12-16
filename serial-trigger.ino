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

        // не принимать новые, пока есть старые...

      int len = sListener.length();
      char* data = sListener.data();

      Serial.print("length: "); Serial.println(len);
      Serial.print("data: "); Serial.println(data);
    }
  }
}

