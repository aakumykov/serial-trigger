#include <Arduino.h>

class Interval
{
  public:
    Interval(unsigned long interval) {
      this->interval = interval;
    }
    
    boolean next(){
      if ((millis() - this->lastRead) > this->interval) {
        this->lastRead = millis();
        return true;
      } else {
        return false;
      }
    }
    
  private:
    unsigned long interval = 200;
    unsigned long lastRead = 0;
};

