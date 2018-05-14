/*
 Bluetooth.h
 */

#ifndef Bluetooth_h
#define Bluetooth_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Action.h"
#include "Rover.h"

class Bluetooth {
  public:
    Bluetooth(SoftwareSerial *serial, bool enabled = false, bool debug = true);
    Action readAction();
    int read();
    bool enabled();
    bool disabled();
  private:
    SoftwareSerial *_serial;
    bool _enabled;
    bool _debug;
};

#endif
