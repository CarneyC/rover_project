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
  _threshold = threshold;
  _debug = debug;
  _stage = 0;
}

/*
  Follow Left Wall
  Fairly rudimentary at this stage, require testing and improvements.
  */
void MazeSolver::solveUnknownMaze() {
  bool frontWall = _frontDistance < _threshold;
  bool leftWall = _leftDistance < _threshold;
  bool rightWall = _rightDistance < _threshold;

  if (leftWall) {
    if (!frontWall) {
      _rover->forward();
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
    _rover->forward();
  }
}

/*
  Require testing
  */
void MazeSolver::solveKnownMaze() {
  bool frontWall = _frontDistance < _threshold;  
  bool leftWall = _leftDistance < _threshold;
  bool rightWall = _rightDistance < _threshold;

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
      _rover->forward();
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
      _rover->forward();
    } else {
      _nextStage();
    }
  }

  // STAGE THREE ---------------------------
  else if (_stage == 3) {
    // Right Wall
    if (rightWall) {
      _rover->forward();
    } else {
      _nextStage();
      _rover->right();
      delay(degreeToDelay(90));
    }
  }

  // STAGE FOUR ------------------------------
  else if (_stage == 4) {
    // No Front Wall
    if (!frontWall) {
      _rover->forward();
    } else {
      _nextStage();
      _rover->left();
      delay(degreeToDelay(90));
    }
  }

  // STAGE FIVE -------------------------------
  else if (_stage == 5) {
      // Right Wall
      if (!leftWall) {
        _rover->forward();
      } else {
        _nextStage();
        _rover->left();
        delay(degreeToDelay(90));
      }
  }

  // STAGE SIX --------------------------------
  else if (_stage == 6) {
      // No Front Wall
      if (!frontWall) {
        _rover->forward();
      } else {
        _nextStage();
        _rover->right();
        delay(degreeToDelay(90));
      }
  }

  // STAGE SEVEN -------------------------------
  else if (_stage == 7) {
    // No Front Wall
    if (!frontWall) {
      _rover->forward();
    }
    else if (rightWall) {
      _nextStage();
      _rover->right();
      delay(degreeToDelay(90));
    }
  }

  else {
    _rover->forward();
  }
}

// Stop Rover if wall is too close
void MazeSolver::keepInBound() {
  if (_rover->lastAction() == Action::Forward && _frontDistance <= _threshold) {
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
  return degree * 20;
}

void MazeSolver::_nextStage() {
  _stage++;
  if (_debug) {
    Serial.print("Proceeding to Stage ");
    Serial.println(_stage);
  }
}

