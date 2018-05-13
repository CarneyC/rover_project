// ROVER CODE 04/05/18
// 06/05/18 Update due to wiring
// 11/05/18 Completely restructured to use classes

/*
  If this doesn't compile,
  Go to Sketch -> Include Library -> Add .ZIP Library
  And select the rover_libs folder in the root folder of this sketch
  */
#include <SoftwareSerial.h>
#include <Sonar.h>
#include <SonarBundle.h>
#include <Motor.h>
#include <Rover.h>
#include <Bluetooth.h>
#include <MazeSolver.h>

/*
  Sonars (trig, echo)
  */
Sonar frontSonar(8, 12);
Sonar leftSonar(11, 13);
Sonar rightSonar(10, 9);
// Wrapper with serial output
SonarBundle sonars(&frontSonar, &leftSonar, &rightSonar, true);

/*
  Motors (forward, reverse)
  Rover  (left, right)
  */
Motor leftMotor(A1, A0);
Motor rightMotor(3, 2);
Rover rover(&leftMotor, &rightMotor);

/*
  Bluetooth (RX, TX)
  */
SoftwareSerial btSerial(4, 5);
Bluetooth bluetooth(&btSerial);

/*
  Maze Solver
  */
MazeSolver maze(&rover, &sonars);

void setup() {
  // starts serial communication, for debugging in rover / bluetooth
  Serial.begin(9600);
}

Action action;
void loop() {
  maze.updateDistance();
  action = bluetooth.readAction();
  rover.setAction(action);

  if (bluetooth.disabled()) {
    maze.solveKnownMaze();
    // This will be togglable by bluetooth eventually
    // maze.solveUnknownMaze();
  }

  maze.keepInBound();
}

