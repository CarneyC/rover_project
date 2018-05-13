/*
 Sonar.h
 */

#ifndef Sonar_h
#define Sonar_h

#include <Arduino.h>

class Sonar {
  public:
    Sonar(int trigPin, int echoPin, int sample = 1);
    double read();
    double readDistance();
    long readDuration();
    long convert(double distance);
    double convert(long duration);
  private:
    int _trigPin;
    int _echoPin;
    int _sample;
    long _max;
};

#endif
