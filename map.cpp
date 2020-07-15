/**
 * Map is used to generate the terrain (height) maps for various biomes.
 * it also sets the material and texture properties for the each biome type.
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
#include "map.h"
#include "PPM.h"
#include "fern.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "tree.h"
#include "seaweed.h"
#include "bush.h"

#define PI 3.14

float m_amb0[4] = {0.2,0.2,0.2,1};
float m_dif0[4]= {0.2,0.2,0.2,1};
float m_spec0[4]= {0.2,0.2,0.2,1};
float shiny0 = 35;
float m_glow0[4] = {0,0,0,0};

float m_amb1[4] = {0.2,0.2,0.2,1};
float m_dif1[4] = {0.6,0.6,0.2,1};
float m_spec1[4]= {0.2,0.2,0.2,1};
float shiny1 = 35;
float m_glow1[4] = {0,0,0,0};

float m_amb2[4] = {0.2,0.2,0.2,1};
float m_dif2[4] = {0.2,0.6,0.2,1};
float m_spec2[4] = {0.2,0.2,0.2,1};
float shiny2 = 35;
float m_glow2[4] = {0,0,0,0};

float m_amb3[4] = {0,0,0.5,0.5};
float m_dif3[4] = {0.2,0.2,0.8,0.5};
float m_spec3[4] = {0,0,0,1};
float shiny3 = 35;
float m_glow3[4] = {0,0,0,0};

float m_amb4[4] = {0,0,0.5,1};
float m_dif4[4] = {0.2,0.8,0.5,1};
float m_spec4[4] = {0.5,0.5,0.5,1};
float shiny4 = 35;
float m_glow4[4] = {0,0,0,1};

float m_amb5[4] = {0.2,0.5,0.5,1};
float m_dif5[4] = {0.2,0.2,0.2,1};
float m_spec5[4] = {0.5,0.5,0.5,1};
float shiny5 = 35;
float m_glow5[4] = {0,0,0,1};

float m_amb6[4] = {0.2,0.2,0.2,1};
float m_dif6[4] = {0.7,0.7,0.7,1};
float m_spec6[4] = {1,1,1,1};
float shiny6 = 35;
float m_glow6[4] = {0,0,0,1};

//min function which returns the lower of a or b
float min(float a, float b){
  if (a <b ){
    return  a;
  }
  return b;
}



//max function which returns the higher of a or b
float max(float a, float b){
  if (a  > b ){
    return a;
  }
  return b;
}


//function to generate a random number
float randomFloat(){
      float x = ((float) rand() / (float) RAND_MAX);
      float y = ((float) rand() / (float) RAND_MAX);
      return x - y;
  }


// the basic construcotr for map, which sets a default size, and creates the map starting from the origin
map::map(){
  size = 10;
  strtx = 0;
  strtz = 0;
  for (int i = 0; i < size; i ++){
    std::vector<Point3D> temp;
    for (int j = 0; j < size; j ++){
      Point3D p (i, randomFloat()/10, j,forest); // the height is a random float, the higher the divisor the more flat the plane will be
      temp.push_back(p);
    }
    mesh.push_back(temp);
  }
}

//constructor that allows you to set the height value. A lower height will cause the y value of the traingles to be higher
map::map(float height){
  size = 10;
  strtx = 0;
  strtz = 0;
  for (int i = 0; i < size; i ++){
    std::vector<Point3D> temp;
    for (int j = 0; j < size; j ++){
      Point3D p (i, randomFloat()/height, j,forest);
      temp.push_back(p);
    }
    mesh.push_back(temp);
  }
}

//constructor with both a height and a size. biomes are inSize x inSize
map::map(float height, int inSize){
  size =inSize;
  strtx = 0;
  strtz = 0;
  for (int i = 0; i < size; i ++){
    std::vector<Point3D> temp;
    for (int j = 0; j < size; j ++){
      Point3D p (i, randomFloat()/height, j,forest);
      temp.push_back(p);
    }
    mesh.push_back(temp);
  }
}

//constructor with a hieght, a size, and an initial x and z coordinates which determine where on a plane a terrain will be drawn

map::map(int inSize, int inX, int inZ){
  size =inSize;
  strtx = inX;
  strtz = inZ;
  for (int i = strtx; i < size+strtx; i ++){
    std::vector<Point3D> temp;
    for (int j = strtz; j < size+strtz; j ++){
      Point3D p (i, 0, j,forest);
      temp.push_back(p);
    }
    mesh.push_back(temp);
  }
}

//randomly chooses the voronoi points for the terrain and then determines what biome each point on the map is
void map::setVoronoi(){
  Point3D vPoints[10];
  biomeType biome;
  for (int i = 0; i < 10; i ++){
    int bio = rand() % 3; //randomly assign each point a biome
    switch (bio){
      case(0):
        biome = hills;
        break;
      case(1):
        biome = desert;
        break;
      case(2):
        biome = forest;
        break;
    }
    Point3D p (rand() % this->size, 0, rand() % this->size, biome);
    vPoints[i] = p;
  }
  for(int j = 0; j < this->size; j++){
    for (int k = 0; k < this->size; k++){
      Point3D close (100000000, 0, 10000000, forest);
      for(int l = 0; l < 10; l++){
        if(this->mesh[j][k].xzDist(vPoints[l])<this->mesh[j][k].xzDist(close)){
          this->mesh[j][k].biome = vPoints[l].biome;
          close = vPoints[l];
        }
      }
    }
  }
}

//set up the heights for each type of terrain
void map::initMap(){
  Point3D* bumps;
  bumps = (Point3D*) malloc (this->size * 10 * sizeof(Point3D));

  for(int k = 0 ; k < this->size * 10; k++){
    int i = rand() % (this->size - 1);
    int j = rand() % (this->size - 1);
    Point3D b (i,0,j,hills);
    *(bumps+k) = b;
  }

  for(int l = 0; l < this->size * 10; l ++){
   for (int m = 0; m < this->size; m++){
     for (int n = 0; n < this->size; n++){
       Point3D pd = bumps[l];
       Point3D pm = this->mesh[m][n];
       if (pd.xzDist(pm) <= this->size/20 && pm.biome == desert){
         this->mesh[m][n].py += 1 + cos(PI*pd.xzDist(pm)*2/(this->size/10))*1;
       }
     }
   }
 }
 	for(int i=0; i<200; i++){
    float v = static_cast <float> (rand());
    float a = sin(v);
    float b = cos(v);
    float d = sqrt(pow(this->size,2) + pow(this->size,2));
    float c = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * d - d/2;
    for(int x = 0; x<this->size; x++){
        for(int z=0; z<this->size; z++){
            if(this->mesh[x][z].biome == hills){
              if (a*x + b*z - c > 0){
                  this->mesh[x][z].py += 0.5;
                }
                else{
                   this->mesh[x][z].py -= 0.5;
                }
            }
        }
      }
    }
    Point3D* bumps1;
    bumps1 = (Point3D*) malloc (this->size * 10 * sizeof(Point3D));

    for(int k = 0 ; k < this->size * 10; k++){
      int i = rand() % (this->size - 1);
      int j = rand() % (this->size - 1);
      Point3D b (i,0,j,hills);
      *(bumps1+k) = b;
    }

    for(int l = 0; l < this->size * 3; l ++){
     for (int m = 0; m < this->size; m++){
       for (int n = 0; n < this->size; n++){
         Point3D pd = bumps1[l];
         Point3D pm = this->mesh[m][n];
         if (pd.xzDist(pm) <= this->size/20 && pm.biome == forest){
          this->mesh[m][n].py += 0.5;
           this->mesh[m][n].py += 1 + cos(PI*pd.xzDist(pm)*2/(this->size/10))*2;
         }
       }
     }
   }
}


//puts points into triangles so they can be drawn and adds trees, bushes and weeds to the map
void map::setMesh(){
  tMap1 = new triangle*[this->size];
  tMap2 = new triangle*[this->size];
  for (int m = 0; m < this->size - 1; m++){
    tMap1[m] = new triangle[this->size];
    tMap2[m] = new triangle[this->size];
    for (int n = 0; n < this->size - 1; n++){
       Point3D p = this->mesh[m][n];
       Point3D p1 = this->mesh[m][n+1];
       Point3D p2 = this->mesh[m+1][n+1];
       Point3D p3 = this->mesh[m+1][n];
       triangle t1 (p, p1, p2);
       triangle t2 (p3, p, p2);
       t1.setFaceNormal();
       t2.setFaceNormal();
       tMap1[m][n] = t1;
       tMap2[m][n] = t2;
       if(rand() % 20 == 0 && this->mesh[m][n].biome == desert){
         fern f (this->mesh[m][n]);
         this->ferns.push_back(f);
       }
       if(rand() % 40 == 0 && this->mesh[m][n].biome == forest){
         tree t (this->mesh[m][n]);
         this->trees.push_back(t);
       }
       if(rand() % 20 == 0 && this->mesh[m][n].biome == forest && this->mesh[m][n].py >= 1){
         bush b (this->mesh[m][n]);
         this->bushes.push_back(b);
       }
       if(rand() % 100 == 0 && this->mesh[m][n].biome == hills && this->mesh[m][n].py <= -5){
         seaweed sw (this->mesh[m][n]);
         this->weeds.push_back(sw);
       }
     }
  }
}

//textures everything in the map
void map::initTextures(){

glMatrixMode(GL_TEXTURE);
glScalef(1,-1,-1);

img_data_grass = stbi_load("moss.png", &width, &height, &max, 0);

img_data_grass_ferns = stbi_load("bush.png", &fwidth, &fheight, &fmax, 0);

img_data_rock = LoadPPM("rock_2.ppm", &width2, &height2, &max2);

img_data_sand = LoadPPM("sand_2.ppm", &width3, &height3, &max3);

img_data_spruce = stbi_load("spruce.png", &swidth, &sheight, &smax, 0);

img_data_seaweed = stbi_load("vine.png", &vwidth, &vheight, &vmax, 0);

img_data_bush = stbi_load("bush.png", &bwidth, &bheight, &bmax, 0);

img_data_snow = stbi_load("snow.jpg", &snoww, &snowh, &snowm, 0);

glEnable(GL_TEXTURE_2D);

glGenTextures(8, textures);

glBindTexture(GL_TEXTURE_2D, textures[0]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data_grass);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[1]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data_rock);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[2]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data_sand);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[3]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fwidth, fheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data_grass_ferns);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[4]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, swidth, sheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data_spruce);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[5]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vwidth, vheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data_seaweed);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[6]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bwidth, bheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data_bush);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glBindTexture(GL_TEXTURE_2D, textures[7]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, snoww, snowh, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data_snow);

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void map::drawWeeds(){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec5);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow5);
  for(int i = 0; i < this->weeds.size(); i ++){
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    weeds[i].drawWeed();
  }
}

//drawns ferns on the map
void map::drawFerns(){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec4);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow4);
  for(int i = 0; i < this->ferns.size(); i ++){
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    ferns[i].drawFern();
  }
}
//draws bushes
void map::drawBushes(){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec5);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow5);
  for(int i = 0; i < this->bushes.size(); i ++){
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    bushes[i].drawBush();
  }
}

//draws trees
void map::drawTrees(){
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec5);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow5);
  for(int i = 0; i < this->trees.size(); i ++){
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    trees[i].drawTree();
  }
}

//function to draw the generated map
void map::drawMap(){

  for (int i = 0; i < size-1; i ++){
    for(int j = 0; j < size-1; j ++){
      GLint tex;
      switch (this->mesh[i][j].biome){
          case hills:

          if(this->mesh[i][j].py >= 12){
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb6);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif6);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec6);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny6);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow6);
            tex = textures[7];
          }
          else {
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb0);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif0);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec0);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny0);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow0);
            tex = textures[1];
          }
          break;
          case desert:
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb1);
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif1);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec1);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny1);
          glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow1);
          tex = textures[2];
          break;
          case forest:
          glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb2);
          glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif2);
          glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec2);
          glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny2);
          glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow2);
          tex = textures[0];
          break;
        }
      triangle t1 = tMap1[i][j];
      triangle t2 = tMap2[i][j];
      glBindTexture(GL_TEXTURE_2D, tex);
      t1.drawTriangle();
      t2.drawTriangle();
    }
  }
  this->drawWeeds();

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec3);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_glow3);

    glBegin(GL_POLYGON);
      glVertex3f(this->strtx, 0.95, this->strtz);
      glVertex3f(this->strtx, 0.95, this->strtz + size);
      glVertex3f(this->strtx + size, 0.95, this->strtz+size);
     glVertex3f(this->strtx + size, 0.95, this->strtz);
    glEnd();
    glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);

    this->drawFerns();

    this->drawBushes();

    this->drawTrees();

}
