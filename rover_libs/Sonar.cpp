/*
 Sonar.cpp
 */

#include <Arduino.h>
#include <math.h>
#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin, int sample) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  _trigPin = trigPin;
  _echoPin = echoPin;
  _sample = sample;

  // upper bound of sound travel duration
  _max = 130000;
}

/*
  Read Distance in cm
  */
double Sonar::read() {
  return readDistance();
}

double Sonar::readDistance() {
  float duration;
  long min = _max;
  for (int i = 0; i < _sample; i++) {
    duration = readDuration();
    if (duration >= _max || isnan(duration)) {
      return convert(_max);
    }
    if (duration < min) min = duration;
  }
  return convert(min);
}

/*
  Read sound wave travel duration in microseconds
  */
long Sonar::readDuration() {
  // Clears the output pin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Output sound wave
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Return the sound wave travel time in microseconds
  return pulseIn(_echoPin, HIGH);
}

/*
  Convert cm to ms / ms to cm
  */
long Sonar::convert(double distance) {
  return distance / 0.017;
}

double Sonar::convert(long duration) {
  return duration * 0.017;
}
