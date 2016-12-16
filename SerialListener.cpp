#include <Arduino.h>

class SerialListener
{
  public:
    SerialTrigger() {}

    void wait() {

      if (Serial.available() > 0) {
        Serial.println("serial available");
        byte piece = Serial.read();
        
        if (piece != ';') {
          
          this->tempData[this->tempDataCount++] = piece;
        
        } else {
          
          this->inputData = this->tempData;
          this->inputDataLength = this->tempDataCount;
          
          this->dataRecieved = true;
          
          this->tempData = NULL;
          this->tempDataCount = 0;
        }
      }
    }

    boolean recieved() {
      return this->dataRecieved;
    }

    char* data(){
      char* d = this->inputData;
      this->clear();
      return d;
    }

    int length() {
      return this->inputDataLength;
    }

    void clear() {
      this->inputData = NULL;
      this->dataRecieved = false;
      //this->inputDataLength = 0; // Нельзя обнулять, чтобы не зависеть от порядка использования функций.
    }

  private:
    // настраиваемые пользователем
    char delimiter = ";";
    unsigned long checkInterval = 200; //ms
    boolean echo = false;

    // служебные
    boolean dataRecieved = false;
    
    char* tempData = new char;
    int tempDataCount = 0;
    
    char* inputData = new char;
    int inputDataLength = 0;
};


