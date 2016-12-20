#include "SerialListener.cpp"
#include "Interval.cpp"

SerialListener sListener(512, ';');
Interval interval(3000);

void setup() {
  Serial.begin(9600);
  Serial.println("=serial-trigger=");
  Serial.println("setup()");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.isRecieved()){

      int len = sListener.dataLength();
      char* data = sListener.data();
      
      //Serial.print("main loop: data recieved, length is ");
      Serial.println(len); // раскомментирование этой строки нарушает работу!
      
      //Serial.println("data: ");
      Serial.println(data);
      
//      Serial.println("qwerty");  // раскомментирование этой строки нарушает работу!
      
      //Serial.print("data: "); // раскомментирование этой строки нарушает работу!
//      Serial.println(sListener.data());

      //sListener.clear();
    }
  }
}

