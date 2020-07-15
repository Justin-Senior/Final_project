#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "map.h"

#ifndef OVERHEAD_H
#define OVERHEAD_H

class overhead{

public:
  overhead(map terrain);

  int size;
  std::vector<std::vector<Point3D>> heightMap;

  void updateMap(map terrain);

};

#endif
