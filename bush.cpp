/**
 * This class is used to draw bushes across our map.
 * */
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "bush.h"

bush::bush(Point3D loc){

  location = loc;

}

void bush::drawBush(){
  glDisable(GL_CULL_FACE);
  glColor4f(0,0,0,0);
  glBegin(GL_QUADS);
  //bushes are drawn  as a set of vertices.
    glTexCoord2f(0,0);
    glVertex3f(this->location.px-0.5, this->location.py, this->location.pz);
    glTexCoord2f(1,0);
    glVertex3f(this->location.px+0.5, this->location.py, this->location.pz);
    glTexCoord2f(1,1);
    glVertex3f(this->location.px+0.5, this->location.py+1, this->location.pz);
    glTexCoord2f(0,1);
    glVertex3f(this->location.px-0.5, this->location.py+1, this->location.pz);

    glTexCoord2f(0,0);
    glVertex3f(this->location.px, this->location.py, this->location.pz -0.5);
    glTexCoord2f(1,0);
    glVertex3f(this->location.px, this->location.py, this->location.pz + 0.5);
    glTexCoord2f(1,1);
    glVertex3f(this->location.px, this->location.py+1, this->location.pz + 0.5);
    glTexCoord2f(0,1);
    glVertex3f(this->location.px, this->location.py+1, this->location.pz - 0.5);
  glEnd();
  glEnable(GL_CULL_FACE);
}
