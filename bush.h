#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"

#ifndef BUSH_H
#define BUSH_H

class bush{

public:
  bush(Point3D loc);

  Point3D location;

  void drawBush();

};
#endif
