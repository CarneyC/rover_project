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
    MazeSolver(Rover *rover, SonarBundle *sonars, double threshold = 10.0, double _angleModifier = 4.4, bool debug = true);
    void solveKnownMaze();    
    void followLeftWall();
    void followRightWall();
    void updateDistance();
    void keepInBound();
    int degreeToDelay(int degree);
    void reset();
  private:
    // functions
    void _init();
    void _nextStage();
    void _forward();
    // variables
    Rover *_rover;
    SonarBundle *_sonars;
    double _frontThreshold;
    double _sideThreshold;
    double _angleModifier;
    bool _debug;
    int _stage;
    double _frontDistance;
    double _leftDistance;
    double _rightDistance;
};

#endif
