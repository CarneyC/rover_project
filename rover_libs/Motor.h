/*
 Motor.h
 */

#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int fwdPin, int revPin);
    void forward();
    void reverse();
    void stop();
  private:
    int _fwdPin;
    int _revPin;
};

#endif
