/*
 Rover.cpp
 */

#include <Arduino.h>
#include "Rover.h"
#include "Motor.h"
#include "Action.h"

Rover::Rover(Motor *leftMotor, Motor *rightMotor, bool debug) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
  _debug = debug;
}

/*
  Directional Controls
  */  
void Rover::forward() {
  setAction(Action::Forward);
}
void Rover::reverse() {
  setAction(Action::Reverse);
}
void Rover::left() {
  setAction(Action::Reverse);
}
void Rover::right() {
  setAction(Action::Right);
}
void Rover::stop() {
  setAction(Action::Stop);
}

/*
  For controlling rover direction w/ debugging / State tracking
  Will return false if same action is being performed.
  */
bool Rover::setAction(Action action) {
  if (_lastAction == action) return false;
  String direction;
  switch (action) {
    case Action::None:
      return false;
    case Action::Forward:
      _forward();
      direction = "Going Forward...";
      break;
    case Action::Reverse:
      _reverse();
      direction = "Reversing...";
      break;
    case Action::Left:
      _left();
      direction = "Turning Left...";
      break;
    case Action::Right:
      _right();
      direction = "Turning Right...";
      break;
    case Action::Stop:
      _stop();
      direction = "Stopping...";
      break;
  }
  if (_debug && direction) Serial.println(direction);
  _lastAction = action;
  return true;
}

Action Rover::lastAction() {
  return _lastAction;
}

/*
  Directional Controls Helper Methods
  Will not perform any action, if same method is used in succession
  */
void Rover::_forward() {
  _leftMotor->forward();
  _rightMotor->forward();
}
void Rover::_reverse() {
  _leftMotor->reverse();
  _rightMotor->reverse();
}
void Rover::_left() {
  _leftMotor->reverse();
  _rightMotor->forward();
}
void Rover::_right() {
  _leftMotor->forward();
  _rightMotor->reverse();
}
void Rover::_stop() {
  _leftMotor->stop();
  _rightMotor->stop();
}


