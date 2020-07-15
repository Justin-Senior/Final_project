/**
 * Map is used to generate the terrain (height) maps for various biomes.
 * Currently, the map generation is very similar for all biomes but for the final submission this will be changed.
 * */
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "triangle.h"
#include "fern.h"
#include "tree.h"
#include "seaweed.h"
#include "bush.h"

#ifndef MAP_H
#define MAP_H

float randomFloat();

class map{

public:
  int size; //size of the map. maps are size x size
  map();
  map(float height);
  map(float height, int size);
  map(int size, int startX, int startZ);
  std::vector<std::vector<Point3D>> mesh; //map mesh, which is defined as a list of points

  std::vector<fern> ferns;
  std::vector<tree> trees;
  std::vector<seaweed> weeds;
  std::vector<bush> bushes;

  int strtx;
  int strtz;

  triangle **tMap1; //trianlge arrays
  triangle **tMap2;

  GLubyte* img_data_rock;
  GLubyte* img_data_sand;
  GLubyte* img_data_grass;
  unsigned char * img_data_grass_ferns;
  unsigned char * img_data_spruce;
  unsigned char * img_data_seaweed;
  unsigned char * img_data_bush;
  unsigned char * img_data_snow;
  unsigned char * img_data_clouds;

  int width, height, max, width2, height2, max2, width3, height3, max3;
  int fwidth, fheight, fmax, swidth, sheight, smax;
  int vwidth, vheight, vmax, bheight, bwidth, bmax;
  int snoww, snowh, snowm;

  GLuint textures[8];

  void setVoronoi(); //set voronoi cells for biomes
  void initMap(); //set the heightmap of the terrain
  void initTextures();

  void setMesh(); //store triangle mesh in arrays
  void drawWeeds();
  void drawTrees();
  void drawFerns();
  void drawBushes();
  void drawMap();

};

#endif
