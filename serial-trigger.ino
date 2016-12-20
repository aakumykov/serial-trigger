#include "SerialListener.cpp"
#include "Interval.cpp"

SerialListener sListener(512, ';');
Interval interval(500);

void setup() {
  Serial.begin(9600);
  Serial.println("=serial-trigger=");
  Serial.println("setup()");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.isRecieved()){

      Serial.print("main loop: data recieved, length is ");
      Serial.println(sListener.dataLength());

      sListener.data();

      sListener.clear();

//      Serial.print("data: ");
//      Serial.println(sListener.data());
    }
  }
}

