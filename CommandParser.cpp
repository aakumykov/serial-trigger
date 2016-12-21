#include <Arduino.h>

class CommandParser
{
  public:
    CommandParser(char* command_delimiter = ":", char* data_delimiter = ","){
      this->command_delimiter = command_delimiter;
      this->data_delimiter = data_delimiter;
    }

  void parse(char* inputData) {
    Serial.print("CommandParser.parse(");
    Serial.print(inputData);
    Serial.println(")");
    
    /* Ноль - неверная команда (может быть передан как прямо,
     так и появиться, если команда состоит из букв, а не цифр). */
     
    this->raw_command = strtok(inputData, this->command_delimiter);
    this->the_command = atoi(this->raw_command);

//    Serial.print("the_command: ");
//    Serial.println(this->the_command);

    Serial.println(this->the_data[0]);
    Serial.println(this->the_data[1]);
    Serial.println(this->the_data[2]);
    Serial.println(this->the_data[3]);

    this->raw_data = strtok(NULL, this->data_delimiter);
    
    while (this->raw_data != NULL) {
      Serial.print("raw_data");
      Serial.print(this->the_counter);
      Serial.print(": ");
      Serial.print(this->raw_data);
      Serial.print(", ");
      Serial.print("atoi: ");
      Serial.print(atoi(this->raw_data));
      Serial.print(", ");

      Serial.print("the_data");
      Serial.print(this->the_counter);
      Serial.print(": ");
      Serial.print(this->the_data[this->the_counter]);
      
      this->the_data[this->the_counter] = atoi(this->raw_data);
      
      Serial.print(" -> ");
      Serial.println(this->the_data[this->the_counter]);
      
      this->the_counter += 1;
      
      this->raw_data = strtok(NULL, this->data_delimiter);
    }

    Serial.print("the_counter: "); Serial.println(this->the_counter);

    Serial.println("the_data:");
    for (int i=0; i < this->the_counter; i++) {
      Serial.print(i);
      Serial.print(": ");
      Serial.println(this->the_data[i]);
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
    // задаются пользователем
    char* command_delimiter;
    char* data_delimiter;

    // служебные
    char* raw_command;
    int the_command;

    char* raw_data;
    int* the_data = new int[512];

    int the_counter = 0;
};


