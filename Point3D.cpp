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
#include "Point3D.h"

Point3D::Point3D(){
  px = 0;
  py = 0;
  pz = 0;
  biome = forest;
}

Point3D::Point3D(int x, float y, int z, biomeType bio){
  px = x;
  py = y;
  pz = z;
  biome = bio;
}

float* Point3D::coords(){
  static float coords[3];
  coords[0] = px;
  coords[1] = py;
  coords[2] = pz;

  return coords;
}

float Point3D::xzDist(Point3D p2){
  float x1 = this->px;
  float z1 = this->pz;
  float x2 = p2.px;
  float z2 = p2.pz;

  float x3 = pow((x2 - x1),2);
  float z3 = pow((z2 - z1),2);

  return sqrt(x3 + z3);
}
