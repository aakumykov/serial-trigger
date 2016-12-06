#include "SerialTrigger.cpp"

SerialTrigger sTrigger("start");

void setup() {
  Serial.begin(9600);
  Serial.println("setup complete");
}

void loop() {
  sTrigger.wait();

  if (sTrigger.triggered()){
    Serial.println("TRIGGER");
    sTrigger.clear();
  }
}

