#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "map.h"
#include "overhead.h"

//set overview kap as terrain heighmap
overhead::overhead(map terrain){
  heightMap = terrain.mesh;
  size = terrain.size;
}
//update overview map
void overhead::updateMap(map terrain){
  this->heightMap=terrain.mesh;
}
