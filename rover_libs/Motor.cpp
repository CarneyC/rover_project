/*
 Rover.cpp
 */

#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int fwdPin, int revPin) {
  pinMode(fwdPin, OUTPUT);
  pinMode(revPin, OUTPUT);
  _fwdPin = fwdPin;
  _revPin = revPin;
}

/*
  Forward
  */
void Motor::forward() {
  digitalWrite(_fwdPin, HIGH);
  digitalWrite(_revPin, LOW);
}

/*
  Reverse
  */
void Motor::reverse() {
  digitalWrite(_fwdPin, LOW);
  digitalWrite(_revPin, HIGH);
}

/*
  Stop
  */
void Motor::stop() {
  digitalWrite(_fwdPin, LOW);
  digitalWrite(_revPin, LOW);
}
