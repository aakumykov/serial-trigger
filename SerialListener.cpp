#include <Arduino.h>

// Прекращает приём новых данных, покуда не использованы текущие (течка).
// При первом считывании хранимых данных освобождается от них, переходит на
// приём новых. Счётчик длины очищается при считывани хранимых данных, но
// не при при считывании счётчика.

class SerialListener
{
  public:
    SerialListener(char delimiter = ';') {
    }

    void wait() {
      
      if (!this->dataRecieved && (Serial.available()>0))
      {
        Serial.println("serial available");
        
        byte piece = Serial.read();
        
        if (piece == ';')
        {
           // защита от "пустых данных"
           if (0 != this->inputDataCounter) {
            // добавляю символ конца строки
            this->inputData[this->inputDataCounter++] = 0;
            this->dataRecieved = true;
           }
        }
        else 
        {
//          Serial.print(this->inputDataCounter);
//          Serial.print(": ");
//          Serial.print(piece); Serial.print(" ("); Serial.print(char(piece)); Serial.print(")");
//          Serial.println("");
          this->inputData[this->inputDataCounter++] = piece;
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
      Serial.println("");
      Serial.println("----- SerialListener.data() -----");

        for (int i=0; i<this->inputDataCounter; i++) {
          Serial.print(i); Serial.print(": ");
          Serial.print(this->inputData[i]);
          Serial.print(" [code: "); Serial.print(byte(this->inputData[i])); Serial.print("]");
          Serial.println("");
        }

      Serial.println("----- SerialListener.data() -----");

      // копирование файлов в новый массив
      char* d = new char[this->inputDataCounter];

      for (int i=0; i<this->inputDataCounter; i++) {
        d[i] = this->inputData[i];
      }

//      strcpy(d, this->inputData);

      // осичтка текущего массива (хранилища)
      //this->clear();
      
//      return d;
    }

  private:
    // настраиваемые пользователем
    char delimiter;

    // служебные
    int maxInputLength = 512;
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


