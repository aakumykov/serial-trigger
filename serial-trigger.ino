#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

SerialListener sListener;
Interval interval(10);
CommandParser cmdParser;

void setup() {
  Serial.begin(9600);
  Serial.println("=setup complete=");
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
//      for (int i=0; i<data_length; i++) {
//        Serial.println(char_data[i]);
//      }

      cmdParser.parse(char_data);

      char* command = cmdParser.command();
      int* data = cmdParser.data();
      int count = cmdParser.length();
      
      Serial.print("command: ");
      Serial.println(command);

      Serial.print("count: ");
      Serial.println(count);
      
      Serial.println("data: ");
      for (int i=0; i<count; i++) { Serial.println(data[i]); }
    }
  }
}

