#include <math.h>		// For math routines (such as sqrt & trig).
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"

#ifndef TREE_H
#define TREE_H

class tree{

public:
  tree(Point3D loc);

  Point3D location;

  void drawTree();

};
#endif