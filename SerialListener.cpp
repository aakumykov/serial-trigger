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
      Serial.print("length: "); Serial.println(this->inputDataCounter);
      Serial.print("data: "); Serial.println(this->inputData);
      for (int i=0; i < this->inputDataCounter; i++) {
        Serial.print(this->inputData[i]); Serial.print("|");
      }
      Serial.println("");
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

    // тестовая последовательность:
    // qwertry; Enter
    // 123; Enter

    void clear() {
      delete this->inputData;
      //this->inputData = NULL;
      this->inputData = new char;
      this->inputDataCounter = 0;
      this->dataRecieved = false;
    }
};


