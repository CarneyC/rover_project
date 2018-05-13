/*
 SonarBundle.h
 A wrapper to output debug messages
 */

#ifndef SonarBundle_h
#define SonarBundle_h

#include <Arduino.h>
#include "Sonar.h"

class SonarBundle {
  public:
    SonarBundle(Sonar *frontSonar, Sonar *leftSonar, Sonar *rightSonar, bool debug = true);
    double front();
    double left();
    double right();
  private:
    Sonar *_frontSonar;
    Sonar *_leftSonar;
    Sonar *_rightSonar;
    bool _debug;
};

#endif
