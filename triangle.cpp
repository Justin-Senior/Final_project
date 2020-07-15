#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "triangle.h"
#include "Point3D.h"

triangle::triangle(){
  Point3D p (0,0,0,forest);
  points.push_back(p);
  points.push_back(p);
  points.push_back(p);

  this->normal[0] = 0;
  this->normal[1] = 1;
  this->normal[2] = 0;
}

//creates a triangle
triangle::triangle(Point3D p0, Point3D p1, Point3D p2){

  points.push_back(p0);
  points.push_back(p1);
  points.push_back(p2);

  this->normal[0] = 0;
  this->normal[1] = 1;
  this->normal[2] = 0;

}
//calculates the face normal vector of the triangle
void triangle::setFaceNormal(){
  GLfloat v1[] = {points[0].px, points[0].py, points[0].pz};
  GLfloat v0[] = {points[1].px, points[1].py, points[1].pz};
  GLfloat v2[] = {points[2].px, points[2].py, points[2].pz};

  GLfloat e1[] = {v1[0]-v0[0], v1[1]-v0[1], v1[2]-v0[2]};
  GLfloat e2[] = {v2[0]-v0[0], v2[1]-v0[1], v2[2]-v0[2]};

  static GLfloat normalvec[3];
  static GLfloat prenormalvec[3];
  prenormalvec[0] = e1[1]*e2[2] - e1[2]*e2[1];
  prenormalvec[1] = e1[0]*e2[2] - e1[2]*e2[0];
  prenormalvec[2] = e1[0]*e2[1] - e1[1]*e2[0];
  float len = sqrt(pow(prenormalvec[0],2) + pow(prenormalvec[1],2) + pow(prenormalvec[2],2));
  normalvec[0] = (e1[1]*e2[2] - e1[2]*e2[1])/len;
  normalvec[1] = (e1[0]*e2[2] - e1[2]*e2[0])/len;
  normalvec[2] = (e1[0]*e2[1] - e1[1]*e2[0])/len;
  this->normal[0] = normalvec[0];
  this->normal[1] = normalvec[1];
  this->normal[2] = normalvec[2];
}

//draws the triangle
void triangle::drawTriangle(){
  glBegin(GL_TRIANGLES);
  glNormal3fv(this->normal);
  glTexCoord2f(0,0);
  glVertex3fv(points[0].coords());
  glTexCoord2f(1,1);
  glVertex3fv(points[1].coords());
  glTexCoord2f(0,1);
  glVertex3fv(points[2].coords());
  glEnd();
}
//draw the triangle for wireframe(no normal)
void triangle::drawTriangleWire(){
  glVertex3fv(points[0].coords());
  glVertex3fv(points[1].coords());
  glVertex3fv(points[2].coords());
}
