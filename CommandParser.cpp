#include <Arduino.h>

class CommandParser
{
  public:
    CommandParser(char* command_delimiter = ":", char* data_delimiter = ","){
      this->command_delimiter = command_delimiter;
      this->data_delimiter = data_delimiter;
    }

  void parse(char* inputData) {
    Serial.print("CommandParser.parse(), data: ");
    Serial.println(inputData);

    this->the_data = new int[512];
    
    // Ноль - признак неверной команды.
    this->the_command = atoi( strtok(inputData, this->command_delimiter) );

    char* token;
    token = strtok(NULL, this->data_delimiter);
    while (token != NULL) {
      this->the_data[this->the_counter++] = atoi(token);
      token = strtok(NULL, this->data_delimiter);
    }
  }

  int command(){
    //Serial.println(sizeof(this->the_command));
    return this->the_command;
  }

  int length() {
    return this->the_counter;
  }

  int* data() {
    int* output_data = new int[this->the_counter];
         output_data = this->the_data;
    return output_data;
  }

  private:
    char* command_delimiter;
    char* data_delimiter;

    int the_command;
    int the_counter = 0;
    int* the_data;
};


