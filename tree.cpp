#include <math.h>		// For math routines (such as sqrt & trig).
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "Point3D.h"
#include <GL/glut.h>	// OpenGL Graphics Utility Library
#include "tree.h"

tree::tree(Point3D loc) {
    location = loc;
}

void tree::drawTree() {
    GLUquadricObj* myReusableQuadric = 0;
    float radiusBase = 2;
    float radiusTop =1;
    float height = 2;
    int slices = 8;
    int stacks = 8;
    //check that meory was allocated for cylinder
    	if ( ! myReusableQuadric ) {
		myReusableQuadric = gluNewQuadric();
		gluQuadricTexture( myReusableQuadric, GL_TRUE );
	}
    glPushMatrix();
    glTranslated(location.px,location.py,location.pz); // need to move tree to right area
	   glColor4f(0.647,0.165,0.165,0); //brown
     glRotatef(270,1,0,0);
     glScalef(0.25,0.25,2);
	gluCylinder( myReusableQuadric, radiusBase, radiusTop, height, slices, stacks );

    // Draw the top disk cap
	glPushMatrix();
	glTranslated(0.0, 0.0, height);
	glColor4f(0,1,0,0); //green
	gluSphere( myReusableQuadric, 2*radiusTop, slices, stacks);
	glPopMatrix();

	// Draw the bottom disk cap
	glPushMatrix();
	glRotated(180.0, 1.0, 0.0, 0.0);
	gluDisk( myReusableQuadric, 0.0, radiusBase, slices, stacks );
	glPopMatrix();
    glPopMatrix();

}
