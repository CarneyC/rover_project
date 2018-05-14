/*
 Rover.h
 */

#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include "Motor.h"
#include "Action.h"

class Rover {
  public:
    Rover(Motor *leftMotor, Motor *rightMotor, bool debug = true);
    Action lastAction();
    // Directional Controls
    void forward();
    void reverse();
    void left();
    void right();
    void stop();
    bool setAction(Action action);
  private:
    // functions
    void _forward();
    void _reverse();
    void _left();
    void _right();
    void _stop();
    // variables
    Motor *_leftMotor;
    Motor *_rightMotor;
    Action _lastAction;
    bool _debug;
    uint32_t _begin;
};

#endif
