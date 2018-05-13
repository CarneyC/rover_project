/*
 MazeSolver.h
 */

#ifndef MazeSolver_h
#define MazeSolver_h

#include <Arduino.h>
#include "Rover.h"
#include "SonarBundle.h"

class MazeSolver {
  public:
    MazeSolver(Rover *rover, SonarBundle *sonars, double threshold = 5.0, bool debug = true);
    void solveKnownMaze();    
    void solveUnknownMaze();
    void updateDistance();
    void keepInBound();
  private:
    // functions
    void _nextStage();
    int _degreeToDelay(int degree);
    // variables
    Rover *_rover;
    SonarBundle *_sonars;
    double _threshold;
    bool _debug;
    int _stage;
    double _frontDistance;
    double _leftDistance;
    double _rightDistance;
};

#endif
