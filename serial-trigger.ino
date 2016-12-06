#include "SerialTrigger.cpp"
#include "Interval.cpp"

SerialTrigger sTrigger("start");
Interval interval1000(1000);
Interval interval200(200);

void setup() {
  Serial.begin(9600);
  sTrigger.echoON();
  Serial.println("setup complete");
}

void loop() {
  sTrigger.wait();

//  if (sTrigger.triggered()){
//    Serial.println("TRIGGER");
//    sTrigger.clear();
//  }

  if ( interval1000.next() ) {
    Serial.println( "CHECK INTERVAL 1000, millis: " + String(millis()) );
  }

  if ( interval200.next() ) {
    Serial.println( "CHECK INTERVAL 200, millis: " + String(millis()) );
  }
}

