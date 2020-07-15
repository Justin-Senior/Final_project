/**
 * a small helper class for points. currently used to create triangles and will be used later for weather.
 */
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifndef POINT3D_H
#define POINT3D_H

enum biomeType {hills,desert,forest,water};

class Point3D{

public:

  Point3D();
  Point3D(int x, float y, int z, biomeType bio);

  int px;
  float py;
  int pz;

  GLfloat normal[3];

  biomeType biome;

  float* coords();

  float xzDist(Point3D p2);

};

#endif
