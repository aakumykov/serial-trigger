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

    void clear() {
      this->inputData = NULL;
      this->inputData = new char;
      this->inputDataCounter = 0;
      this->dataRecieved = false;
    }
};


