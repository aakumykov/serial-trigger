#include <Arduino.h>

class SerialTrigger
{
  public:
    SerialTrigger(String triggerWord){
      this->triggerWord = triggerWord;
    }
    
    void wait(unsigned long checkInterval=200){
      if (Serial.available() > 0) {
          this->piece = Serial.read();
          if (this->piece != ';') {
            this->tempString += String(char(this->piece));
          } else {
            this->inputData = this->tempString;
            this->tempString = "";
            if (this->inputData == this->triggerWord) {
              this->isTriggered = true;
              this->inputData = "";
            } else {
              Serial.println(this->inputData);
              this->inputData = "";
            }
          }
      }
    }
    
    boolean triggered(){
      return this->isTriggered;
    }
    
    void clear(){
      this->isTriggered = false;
      this->inputData = "";
    }

    private:
      // настраиваемые пользователем
      String triggerWord;
      String delimiter = ";";
      unsigned long checkInterval = 200; //ms

      // служебные
      boolean isTriggered; // основное свойство
      byte piece;
      String tempString = "";
      String inputData = "";
      unsigned long lastCheck = 0;
};


