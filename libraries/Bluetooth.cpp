/*
 Bluetooth.cpp
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Bluetooth.h"
#include "Action.h"
#include "Rover.h"

Bluetooth::Bluetooth(SoftwareSerial *serial, bool enabled, bool debug) {
  _serial = serial;
  _enabled = enabled;
  _debug = debug;

  // start serial communication
  _serial->begin(9600);
}

/*
  Read command from serial, and return a action object.
  Should be called in loop() to read control from the unit.
  */
Action Bluetooth::readAction() {
  int hex = read();
  if (hex) {
    /*
      Toggle Bluetooth Control, triggered by:
      Grab / Auto Grab / Auto Release
      */
    if (hex >= 0x41 && hex <= 0x43) {
      _enabled = !_enabled;

      // Output debug message to serial
      if (_debug) {
        String message = "Bluetooth ";
        message += _enabled ? "enabled." : "disabled.";
        Serial.println(message);
      }
      return Action::Stop;
    }

    // Release changes the maze solver primary algorithm
    else if (hex == 0x44) {
      return Action::Change;
    }

    else if (_enabled) {
      switch (hex) {
        // Stop
        case 0x30:
          return Action::Stop;

        // Up / Forward
        case 0x38:
          return Action::Forward;

        // Down / Reverse
        case 0x32:
          return Action::Reverse;

        // Left / Rotate Left
        case 0x34:
        case 0x45:
          return Action::Left;

        // Right / Rotate Right
        case 0x36:
        case 0x46:
          return Action::Right;
      }
    }
  }

  return Action::None;
}

/*
  Read bluetooth input, return 0 if no available input
  */
int Bluetooth::read() {
  return _serial->available() > 0 ? _serial->read() : 0;
}

/*
  state of bluetooth module
  */
bool Bluetooth::enabled() {
  return _enabled;
}

bool Bluetooth::disabled() {
  return !enabled();
}
