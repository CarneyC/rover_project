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
// Wrapper with serial output (last argument defined if distance will be printed)
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
Bluetooth bluetooth(&btSerial, false);

/*
  Maze Solver
  Last two arguments are distance threshold and angle modifier
  The modifier maps angle in degrees to delay in ms
  */
MazeSolver maze(&rover, &sonars, 6, 5.5);

void setup() {
  // starts serial communication, for debugging in rover / bluetooth
  Serial.begin(9600);
}

/*
 * 0 = Know Maze
 * 1 = Left Wall
 * 2 = Right Wall
 */
int algo = 0;
void loop() {
  maze.updateDistance();
  
  Action action = bluetooth.readAction();
  if (action == Action::Change) {
    algo = (algo + 1) % 3;
    switch (algo) {
      case 0:
        rover.forward();
        break;
      case 1:
        rover.left();
        break;
      case 2:
        rover.right();
        break;
    }
    delay(1000);
    rover.stop();
  }
  else rover.setAction(action);
  
  if (bluetooth.disabled()) {
    switch (algo) {
      case 0:
      default:
        maze.solveKnownMaze();
        break;
      case 1:
        maze.followLeftWall();
        break;
      case 2:
        maze.followRightWall();
        break;
    }
  }

  maze.keepInBound();
}

