#include "SerialTrigger.cpp"
#include "Interval.cpp"

SerialTrigger sTrigger("start");
Interval interval1(738);
Interval interval2(134);

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

  if ( interval1.next() ) {
    Serial.println( "CHECK INTERVAL "+String(interval1.duration())+", millis: " + String(millis()) );
  }

  if ( interval2.next() ) {
    Serial.println( "CHECK INTERVAL "+String(interval2.duration())+", millis: " + String(millis()) );
  }
}

