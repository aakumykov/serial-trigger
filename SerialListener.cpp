#include <Arduino.h>

// Прекращает приём новых данных, покуда не использованы текущие (течка).
// При первом считывании хранимых данных освобождается от них, переходит на
// приём новых. Счётчик длины очищается при считывани хранимых данных, но
// не при при считывании счётчика.

class SerialListener
{
  public:
    //SerialListener(int maxInputLength, char delimiter) {
    SerialListener(int maxLen, char dlmtr) {
      this->maxInputLength = maxLen;
      this->delimiter = dlmtr;

      this->inputData = new char[this->maxInputLength];
      this->outputData = new char[this->maxInputLength];
    }

    void wait() {
      
      if (!this->dataRecieved && (Serial.available()>0))
      {
        Serial.print("serial data available");
        Serial.print(" ");
        Serial.print(this->inputDataCounter);
        Serial.print(" ");
        
        byte piece = Serial.read();

        Serial.print(piece);
        Serial.print(" ");
        Serial.print(char(piece));
        Serial.println("");
        
        if (piece == this->delimiter)
        {
           // защита от "пустых данных"
           if (0 != this->inputDataCounter) 
           {
              // добавляю символ конца строки
              this->inputData[this->inputDataCounter] = char(0);
              this->inputDataCounter += 1;
              this->dataRecieved = true;
  
              Serial.println("");
              Serial.println("data just recieved:");
              Serial.print("length: "); Serial.println(this->inputDataCounter);
              Serial.print("data: "); Serial.println(this->inputData);

              Serial.println("");
              Serial.println("output in for cycle:");
              Serial.println(this->inputDataCounter);
              for (int j=0; j < this->inputDataCounter; j++) {
                Serial.print(this->inputData[j]);
              } Serial.println("");

              Serial.println("");
              Serial.println("output in for abcde with assignment:");
              Serial.println(this->inputDataCounter);
              for (int j=0; j < this->inputDataCounter; j++) {
                this->outputData[j] = this->inputData[j];
                //Serial.print(this->outputData[j]);
                Serial.print(this->inputData[j]);
              } Serial.println("");
           }
        }
        else 
        {
//          Serial.print(this->inputDataCounter);
//          Serial.print(": ");
//          Serial.print(piece); Serial.print(" ("); Serial.print(char(piece)); Serial.print(")");
//          Serial.println("");
          this->inputData[this->inputDataCounter] = char(piece);
          this->inputDataCounter += 1;
        }
      }
    }

    boolean recieved() {
      return this->dataRecieved;
    }

    int length() {
      return this->inputDataCounter;
    }

    char* data() {
//      Serial.println("");
//      Serial.println("----- SerialListener.data(1) -----");
//
//        for (int i=0; i < this->inputDataCounter; i++) {
//          Serial.print(i); Serial.print(": ");
//          Serial.print(this->inputData[i]);
//          Serial.print(" [code: "); Serial.print(byte(this->inputData[i])); Serial.print("]");
//          Serial.println("");
//        }
//
//      Serial.println("----- SerialListener.data(1) -----");

      // копирование файлов в новый массив
      //char* d = new char[512];

      //Serial.print("this->inputDataCounter: "); Serial.println(this->inputDataCounter);
      
//      for (int j=0; j < this->inputDataCounter; j++) {
//        Serial.println(this->inputData[j]);
//        this->outputData[j] = this->inputData[j];
//        //this->someByte = this->inputData[j];
//      }

//      Serial.println("");
//      Serial.println("----- SerialListener.data(2) -----");
//
//        for (int k=0; k < this->inputDataCounter; k++) {
//          Serial.print(k); Serial.print(": ");
//          Serial.print(this->outputData[k]);
//          Serial.print(" [code: "); Serial.print(byte(this->outputData[k])); Serial.print("]");
//          Serial.println("");
//        }
//
//      Serial.println("----- SerialListener.data(2) -----");

      // осичтка текущего массива (хранилища)
      //this->clear();
      this->dataRecieved = false;
      
      return this->outputData;
    }

  private:
    // настраиваемые пользователем
    int maxInputLength;
    char delimiter;

    // служебные
    char* inputData;
    char* outputData;
    int inputDataCounter = 0;
    boolean dataRecieved = false;
    char someByte;

    void clear() {
      delete this->inputData;
      this->inputData = new char[this->maxInputLength];
      this->inputDataCounter = 0;
      this->dataRecieved = false;
    }
};


