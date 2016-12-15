#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

SerialListener sListener;
Interval interval(10);
CommandParser cmdParser;

void setup() {
  Serial.begin(9600);
  Serial.println("setup complete");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    if (sListener.recieved()){
      String string_data = sListener.data();
      int data_length = string_data.length();
      Serial.print("string_data: ");
      Serial.print(string_data);
      Serial.println(" (" + String(data_length) + ")");

      char* char_data = new char[data_length+1];
      string_data.toCharArray(char_data, data_length+1);
      for (int i=0; i<data_length; i++) {
        Serial.println(char_data[i]);
      }
      
      Serial.print("RECIEVED DATA: ");
      Serial.println( String(char_data) );
      
      //cmdParser.parse(sListener.data());
    }
  }
}

