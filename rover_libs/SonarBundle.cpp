/*
 SonarBundle.cpp
 A wrapper to output debug messages
 */

#include <Arduino.h>
#include "Sonar.h"
#include "SonarBundle.h"

SonarBundle::SonarBundle(Sonar *frontSonar, Sonar *leftSonar, Sonar *rightSonar, bool debug) {
  _frontSonar = frontSonar;
  _leftSonar = leftSonar;
  _rightSonar = rightSonar;
  _debug = debug;
}

/*
  Read Distance in cm, and output to serial monitor
  */
double SonarBundle::front() {
  double distance = _frontSonar->readDistance();
  if (_debug) {
    Serial.print("Front (cm): ");
    Serial.println(distance);
  }
  return distance;
}

double SonarBundle::left() {
  double distance = _leftSonar->readDistance();
  if (_debug) {
    Serial.print("Left (cm): ");
    Serial.println(distance);
  }
  return distance;
}

double SonarBundle::right() {
  double distance = _rightSonar->readDistance();
  if (_debug) {
    Serial.print("Right (cm): ");
    Serial.println(distance);
  }
  return distance;
}
