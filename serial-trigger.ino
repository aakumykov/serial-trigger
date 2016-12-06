#include "SerialTrigger.cpp"

SerialTrigger sTrigger("start");

void setup() {
  Serial.begin(9600);
  Serial.println("setup complete");
  
  sTrigger.echoON();
}

void loop() {
  sTrigger.wait();

  if (sTrigger.triggered()){
    Serial.println("TRIGGER");
    sTrigger.clear();
  }
}

