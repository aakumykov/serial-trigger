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
        byte piece = Serial.read();
        
        if (piece == ';')
        {
          // добавляю символ конца строки
          this->inputData[this->inputDataCounter++] = 0;
          this->dataRecieved = true;
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
      Serial.println("----- SerialListener.data() -----");
//      Serial.print("length: "); Serial.println(this->inputDataCounter);
//      Serial.print("data: "); Serial.println(this->inputData);
//      for (int i=0; i < (this->inputDataCounter-1); i++) {
//        Serial.print(this->inputData[i]); Serial.print("|");
//      }
//      Serial.println("");

        for (int i=0; i<this->inputDataCounter; i++) {
          Serial.print(i); Serial.print(": ");
          Serial.print(this->inputData[i]);
          Serial.print(" [code: "); Serial.print(byte(this->inputData[i])); Serial.print("]");
          Serial.println("");
        }

      Serial.println("----- SerialListener.data() -----");
      
      char* d = this->inputData;
      this->clear();
      return d;
    }

  private:
    // настраиваемые пользователем
    char delimiter;

    // служебные
    boolean dataRecieved = false;
    char* inputData = new char;
    int inputDataCounter = 0;

    // тестовая последовательность 1:
    // qwertry; Enter
    // 123; Enter

    // тестовая последовательность 2:
    // abc; Enter
    // 123456; Enter
    // qwerty; Enter
    // 1; Enter
    // 2; Enter
    // 123; Enter

    void clear() {
      delete this->inputData;
      //this->inputData = NULL;
      this->inputData = new char;
      this->inputDataCounter = 0;
      this->dataRecieved = false;
    }
};


