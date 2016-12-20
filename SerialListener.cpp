#include <Arduino.h>

class SerialListener
{
  public:
    SerialListener(int maxLen, char dlmtr) {
      this->maxInputLength = maxLen;
      this->delimiter = dlmtr;

      this->inputData = new char[this->maxInputLength];
    }

    void wait() {
      
      if (!this->dataRecieved && (Serial.available()>0))
      {
        Serial.println("data is available");
        
        byte piece = Serial.read();
        
        if (piece == this->delimiter && (0 != this->len))
        {
          // завершаю приём
          Serial.println("RECIEVE COMPLETE");
          this->inputData[this->len] = char(0);
          this->len += 1;
          this->dataRecieved = true;
        }
        else 
        {
          // продолжаю приём
          Serial.println("continue recieving...");
          this->inputData[this->len] = char(piece);
          this->len += 1;
        }
      }
    }

    boolean isRecieved() {
      //Serial.println("SerialListener.isRecieved()");
      return this->dataRecieved;
    }

    int length() {
      Serial.println("SerialListener.length()");
      return this->len;
    }

    char* data() {
      Serial.println("SerialListener.data()");

      this->outputData = new char[this->len];
      
      for (int i=0; i < this->len; i++) {
        this->outputData[i] = this->inputData[i];
      }

      this->clear();
      
      return this->outputData;
    }

  private:
    // настраиваемые пользователем
    int maxInputLength;
    char delimiter;

    // служебные
    char* inputData;
    char* outputData;
    int len = 0;
    boolean dataRecieved = false;

    void clear() {
      Serial.println("SerialListener.clear()");
      delete this->inputData;
      this->len = 0;
      this->dataRecieved = false;
    }
};


