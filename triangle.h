#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Point3D.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class triangle{

public:
  triangle();
  triangle(Point3D x, Point3D y, Point3D z);

  std::vector<Point3D> points;

  void setFaceNormal();

  void drawTriangle();
  void drawTriangleWire();

  GLfloat normal[3];

};

#endif
