/*
  MazeSolver.cpp
  */

#include <Arduino.h>
#include "MazeSolver.h"
#include "Rover.h"
#include "Action.h"
#include "SonarBundle.h"

MazeSolver::MazeSolver(Rover *rover, SonarBundle *sonars, double threshold, bool debug) {
  _rover = rover;
  _sonars = sonars;
  _frontThreshold = threshold;
  _sideThreshold = threshold * 3.5;
  _debug = debug;
  _stage = 0;
}

/*
  Follow Left Wall
  Fairly rudimentary at this stage, require testing and improvements.
  */
void MazeSolver::solveUnknownMaze() {
  bool frontWall = _frontDistance < _frontThreshold;
  bool leftWall = _leftDistance < _sideThreshold;
  bool rightWall = _rightDistance < _sideThreshold;

  if (leftWall) {
    if (!frontWall) {
      _forward();
    } else if (!rightWall) {
      _rover->right();
      delay(degreeToDelay(90));
    } else {
      _rover->left();
      delay(degreeToDelay(180));
    }
  }
  else {
    _rover->left();
    _forward();
  }
}

/*
  Require testing
  */
void MazeSolver::solveKnownMaze() {
  bool frontWall = _frontDistance < _frontThreshold;
  bool leftWall = _leftDistance < _sideThreshold;
  bool rightWall = _rightDistance < _sideThreshold;

  // STAGE ZERO --------------------------
  if (_stage == 0) {
    if (_debug) {
      Serial.println("----- Initializing pre-scripted maze sequence -----");
      _stage++;
    }
  }

  // STAGE ONE ---------------------------
  if (_stage == 1) {
    // Front Wall
    if (!frontWall) {
      _forward();
    }

    // Front Wall AND Right Side opened
    else if (!rightWall) {
      _nextStage();
      _rover->right();
      delay(degreeToDelay(90));
    }

    // Account for unexpected situation
    else {
      // TODO
      _rover->stop();
    }
  }

  // STAGE TWO -----------------------------
  else if (_stage == 2) {
    // No Right Wall
    if (!rightWall) {
      _forward();
    } else {
      _nextStage();
    }
  }

  // STAGE THREE ---------------------------
  else if (_stage == 3) {
    // Right Wall
    if (rightWall) {
      _forward();
    } else {
      _rover->forward();
      delay(800);
      _rover->right();
      delay(degreeToDelay(90));
      _nextStage();
    }
  }

  // STAGE FOUR ------------------------------
  else if (_stage == 4) {
    if (!frontWall) {
      _forward();
    } else {
      _rover->left();
      delay(degreeToDelay(90));
      _nextStage();
    }
  }

  // STAGE FIVE -------------------------------
  else if (_stage == 5) {
    if (rightWall) {
      _forward();
    } else {
      _nextStage();
    }
  }

  // STAGE SIX --------------------------------
  else if (_stage == 6) {
    // Left wall probably not 45 angle
    if (_frontDistance >= _frontThreshold * 2) {
      _forward();
    } else {
      _rover->left();
      delay(degreeToDelay(90));
      _nextStage();
    }
  }


  // STAGE SEVEN -------------------------------
  else if (_stage == 7) {
    // No Front Wall
    if (!frontWall) {
      _forward();
    } else {
      _nextStage();
      _rover->right();
      delay(degreeToDelay(90));
    }
  }

  else if (_stage == 8) {
    // No Front Wall
    if (!frontWall) {
      _forward();
    }
    else if (!rightWall) {
      _nextStage();
      _rover->right();
      delay(degreeToDelay(90));
    }
  }

  else {
    _forward();
  }
}

// Stop Rover if wall is too close
void MazeSolver::keepInBound() {
  if (_rover->lastAction() == Action::Forward && _frontDistance <= _frontThreshold) {
    _rover->stop();
  }
}

void MazeSolver::updateDistance() {
  _frontDistance = _sonars->front();
  _leftDistance = _sonars->left();
  _rightDistance = _sonars->right();
}

// convert degree angle to rotation time
int MazeSolver::degreeToDelay(int degree) {
  // 1625 / 360
  return degree * 6;
}

void MazeSolver::reset() {
  _stage = 0;
}

void MazeSolver::_nextStage() {
  _stage++;
  _rover->stop();
  if (_debug) {
    Serial.print("Proceeding to Stage ");
    Serial.println(_stage);
  }
}

void MazeSolver::_forward() {
  int threshold = _sideThreshold * 1.2;
  if (_leftDistance < threshold && _rightDistance < threshold) {
    int diff = _leftDistance - _rightDistance;
    _leftDistance > _rightDistance ? _rover->left() : _rover->right();
    delayMicroseconds(100);
  }
  _rover->forward();
  delay(1);
}

