#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"

#ifndef FERN_H
#define FERN_H

class fern{

public:
  fern(Point3D loc);

  Point3D location;

  void drawFern();

};
#endif
