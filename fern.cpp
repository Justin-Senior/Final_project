#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "fern.h"

fern::fern(Point3D loc){

  location = loc;

}

void fern::drawFern(){
  glDisable(GL_CULL_FACE);
  glColor4f(0,0,0,0);
  glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(this->location.px-0.5, this->location.py, this->location.pz);
    glTexCoord2f(1,0);
    glVertex3f(this->location.px+0.5, this->location.py, this->location.pz);
    glTexCoord2f(1,1);
    glVertex3f(this->location.px+0.5, this->location.py+0.5, this->location.pz);
    glTexCoord2f(0,1);
    glVertex3f(this->location.px-0.5, this->location.py+0.5, this->location.pz);

    glTexCoord2f(0,0);
    glVertex3f(this->location.px, this->location.py, this->location.pz -0.5);
    glTexCoord2f(1,0);
    glVertex3f(this->location.px, this->location.py, this->location.pz + 0.5);
    glTexCoord2f(1,1);
    glVertex3f(this->location.px, this->location.py+0.5, this->location.pz + 0.5);
    glTexCoord2f(0,1);
    glVertex3f(this->location.px, this->location.py+0.5, this->location.pz - 0.5);
  glEnd();
  glEnable(GL_CULL_FACE);
}
