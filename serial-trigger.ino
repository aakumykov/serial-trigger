#include <MemoryFree.h>
#include "SerialListener.h"
#include "Interval.h"
#include "CommandParser.h"

Interval interval(10);
SerialListener sListener(256, ';');
CommandParser cParser(128, ":", ",");

void showMem() {
  Serial.print(F("freeMemory()="));
  Serial.println(freeMemory());
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("=serial-trigger="));
  showMem();
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.isRecieved()){

      int len = sListener.dataLength();
      char* data = sListener.data();

      cParser.parse(data);

      Serial.println(F(""));

      int cCommand = cParser.command();
        Serial.print(F("command: "));
        Serial.println(cCommand);
      
      int cLen = cParser.length();
        Serial.print(F("length: "));
        Serial.println(cLen);

      Serial.print(F("data: "));
      int* cData = cParser.data();
      for (int i=0; i < cLen; i++) {
        Serial.print(cData[i]);
        Serial.print(F(","));
      } Serial.println(F(""));

      showMem();
    }
  }
}

