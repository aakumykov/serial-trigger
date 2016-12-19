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
    }

    void wait() {
      
      if (!this->dataRecieved && (Serial.available()>0))
      {
//        Serial.print("serial data available");
//        Serial.print(" ");
//        Serial.print(this->inputDataCounter);
//        Serial.print(" ");
//        Serial.print(sizeof(this->inputData));
//        Serial.print(" ");
//        Serial.print(this->maxInputLength);
//        Serial.println("");
        
        byte piece = Serial.read();
        
        if (piece == this->delimiter)
        {
           // защита от "пустых данных"
           if (0 != this->inputDataCounter) {
            // добавляю символ конца строки
            this->inputData[this->inputDataCounter] = char(0);
            this->inputDataCounter += 1;
            this->dataRecieved = true;

            Serial.println("");
            Serial.println("data just recieved:");
            Serial.print("length: "); Serial.println(this->inputDataCounter);
            Serial.print("data: "); Serial.println(this->inputData);
           }
        }
        else 
        {
//          Serial.print(this->inputDataCounter);
//          Serial.print(": ");
//          Serial.print(piece); Serial.print(" ("); Serial.print(char(piece)); Serial.print(")");
//          Serial.println("");
          this->inputData[this->inputDataCounter] = piece;
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
//      Serial.println("----- SerialListener.data() -----");
//
//        for (int i=0; i<this->inputDataCounter; i++) {
//          Serial.print(i); Serial.print(": ");
//          Serial.print(this->inputData[i]);
//          Serial.print(" [code: "); Serial.print(byte(this->inputData[i])); Serial.print("]");
//          Serial.println("");
//        }
//
//      Serial.println("----- SerialListener.data() -----");

      // копирование файлов в новый массив
      char* d = new char[512];
      
      for (int i=0; i<this->inputDataCounter; i++) {
        Serial.print(this->inputData[i]); Serial.print(", ");
        d[i] = this->inputData[i];
        Serial.print(d[i]);
        Serial.println("");
      }

      // осичтка текущего массива (хранилища)
      this->clear();
      
      return d;
    }

  private:
    // настраиваемые пользователем
    int maxInputLength;
    char delimiter;

    // служебные
    char* inputData = new char[this->maxInputLength];
    int inputDataCounter = 0;
    boolean dataRecieved = false;

    void clear() {
      delete this->inputData;
      this->inputData = new char[this->maxInputLength];
      this->inputDataCounter = 0;
      this->dataRecieved = false;
    }
};


