#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

SerialListener sListener(512, ';');
Interval interval(10);
CommandParser cParser;

void setup() {
  Serial.begin(9600);
  Serial.println("=serial-trigger=");
  //Serial.println("setup()");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.isRecieved()){

      int len = sListener.dataLength();
      char* data = sListener.data();
      
      //Serial.print("main loop: data recieved, length is ");
      //Serial.println(len); 
      
      //Serial.println("dat1a: "); // раскомментирование этой строки нарушает работу!
      Serial.println(data);

      cParser.parse(data);

      char* command = cParser.command();
      Serial.println(command);
      
      int cLen = cParser.length();
      Serial.println(cLen);
      
      int* cData = cParser.data();
      for (int i=0; i < cLen; i++) {
        Serial.print(cData[i]);
      } Serial.println("");
      
      //Serial.println("qwerty");  // раскомментирование этой строки нарушает работу!
      //Serial.print("data: "); // раскомментирование этой строки нарушает работу!
      //Serial.println(sListener.data());
    }
  }
}

