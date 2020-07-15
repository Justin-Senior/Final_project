#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"

#ifndef SEAWEED_H
#define SEAWEED_H

class seaweed{

public:
  seaweed(Point3D loc);

  Point3D location;
  int height;

  void drawWeed();

};
#endif
