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
        ////Serial.println("data is available");
        
        byte piece = Serial.read();
        
        if (piece == this->delimiter && (0 != this->len))
        {
          // завершаю приём
          //Serial.println("RECIEVE COMPLETE");
          this->inputData[this->len] = char(0);
          this->len += 1;
          this->dataRecieved = true;
          //Serial.println(this->inputData);
        }
        else 
        {
          // продолжаю приём
          //Serial.println("continue recieving...");
          this->inputData[this->len] = char(piece);
          this->len += 1;
        }
      }
    }

    boolean isRecieved() {
      ////Serial.println("SerialListener.isRecieved()");
      return this->dataRecieved;
    }

    int dataLength() {
      ////Serial.println("SerialListener.dataLength()");
      return this->len;
    }

    char* data() {
//      Serial.println("SerialListener.data()");
//      Serial.print("this->maxInputLength="); Serial.println(this->maxInputLength);
//
//      Serial.print("this->len=");
//      Serial.println(this->len);

      this->outputData = new char[this->len];
      this->outputData = this->inputData;
      //this->inputData

      for (int i=0; i < this->len; i++) {
//        //this->outputData[i] = this->inputData[i];
        //Serial.print(this->outputData[i]);
      }
      //Serial.println("");

// Три строчки ниже нарушают работу
//      Serial.print("this->outputData=");
//      Serial.println(this->outputData);
////      Serial.println(*this->outputData);

//      this->outputData = new char[this->len];
//      
//      for (int i=0; i < this->len; i++) {
//        this->outputData[i] = this->inputData[i];
//      }

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
      //Serial.println("SerialListener.clear()");
      this->len = 0;
      this->dataRecieved = false;
    }
};


