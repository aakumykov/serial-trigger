#include "SerialListener.cpp"
#include "Interval.cpp"

SerialListener sListener;
Interval interval(10);

void setup() {
  Serial.begin(9600);
  Serial.println("setup complete");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    if (sListener.recieved()){
      Serial.print("RECIEVED DATA: ");
      Serial.println(sListener.data());
    }
  }
}

