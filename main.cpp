/**
 * Authors: Justin Senior & Nikhail Singh
 * Date: December 8th 2019
 * Description: Our final project is a biome generator that randomly generates biomes using voronoi cells.
 * it includes: 4 biomes: rocks, forests, deserts and water.
 * It also includes vegetation for each of these biomes including trees, bushes and seaweed.
 * In the bottom left corner there is a minimap which gives you an overhead view of all of the entire map.
 */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "triangle.h"
#include "map.h"
#include "overhead.h"
#include <time.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Point3D.h"

#define PI 3.14159265 //constant for pi

float hang = 45;

float density = 0.01;
float fogColor[4] = {0.5, 0.5, 0.5, 1};

bool pause = true; // if pause is false the program will freeze


//sets up the camera
GLdouble eye[] = { 10, 2, 10 };
GLdouble lookAt[] = { 1, 0, 1};
GLdouble up[] = { 0, 1, 0 };


//Light specs
float pos[4] = {0, 100, 0, 0};
float amb[4] = {1,1,1, 1};
float dif[4] = {1,1,1, 1};
float spc[4] = {1,1,1,0.5};

float pos1[4] = {0, 3, 0, 1};
float amb1[4] = {1,1,1, 1};
float dif1[4] = {1,1,1, 1};
float spc1[4] = {1,1,1,0.5};

const int H =100;

map terrain(H,0,0);

unsigned int data[2*H][2*H][3]; //data used for textures
GLint WindowID1, WindowID2;
overhead over (terrain); //instance of overhead to draw overhead map.

//function to set texturing data for each biome type
void setData(){
  for( int y = 0; y < H*2; y += 2 ) {
      for( int x = 0; x < H*2; x += 2 ) {
        if(over.heightMap[x/2][y/2].py < 1.5){
          data[y][x][0] = (0.5) * 256 * 256 * 256 * 256;
          data[y][x][1] = (0.5) * 256 * 256 * 256 * 256;
          data[y][x][2] = (0.8) * 256 * 256 * 256 * 256;
          data[y+1][x][0] = (0.5) * 256 * 256 * 256 * 256;
          data[y+1][x][1] = (0.5) * 256 * 256 * 256 * 256;
          data[y+1][x][2] = (0.8) * 256 * 256 * 256 * 256;
          data[y+1][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
          data[y+1][x+1][1] = (0.5) * 256 * 256 * 256 * 256;
          data[y+1][x+1][2] = (0.8) * 256 * 256 * 256 * 256;
          data[y][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
          data[y][x+1][1] = (0.5) * 256 * 256 * 256 * 256;
          data[y][x+1][2] = (0.8) * 256 * 256 * 256 * 256;
        }
        else {
          if (over.heightMap[x/2][y/2].biome == forest){
            data[y][x][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
          }
          if (over.heightMap[x/2][y/2].biome == desert){
            data[y][x][0] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][0] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][0] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x+1][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y+1][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][0] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x+1][1] = (0.8) * 256 * 256 * 256 * 256;
            data[y][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
          }
          if (over.heightMap[x/2][y/2].biome == hills){
            data[y][x][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x][1] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][1] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][1] = (0.5) * 256 * 256 * 256 * 256;
            data[y+1][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][0] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][1] = (0.5) * 256 * 256 * 256 * 256;
            data[y][x+1][2] = (0.5) * 256 * 256 * 256 * 256;
          }

        }
      }
  }
}

//function to sett up lighting
void light(){
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spc);

  glLightfv(GL_LIGHT1, GL_POSITION, pos1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, dif1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
  glLightfv(GL_LIGHT1, GL_SPECULAR, spc1);
}

//function to handle reshape
void handleReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
}

//function that handles passive mouse movement
void passive(int x, int y){
  if (x < glutGet(GLUT_WINDOW_WIDTH)/2 - 5){
    hang += .03;
    lookAt[0] = 1000*sin(hang);
    lookAt[2] = 1000*cos(hang);
  }
  if (x > glutGet(GLUT_WINDOW_WIDTH)/2 + 5){
    hang -= .03;
    lookAt[0] = 1000*sin(hang);
    lookAt[2] = 1000*cos(hang);
  }
  if (y < glutGet(GLUT_WINDOW_HEIGHT)/2 - 5){
    lookAt[1] += 20;
  }
  if (y > glutGet(GLUT_WINDOW_HEIGHT)/2 + 5){
    lookAt[1] -= 20;
  }
}

//TODO fix crashing when camera near map border caused by indexing aout of bounds
void setEyeHeight(){
  float next[2] = {eye[0] + lookAt[0]/500, eye[2] + lookAt[2]/500};
  Point3D eyePoint (eye[0], 0, eye[2], forest);
  Point3D nextPoint (lookAt[0]/500, 0, lookAt[2]/500, forest);
  eye[1] = (terrain.mesh[eye[0]][eye[2]].py + terrain.mesh[next[0]][next[1]].py)/2 + 2;
}

//function to handle key presses
void keyboard(unsigned char key, int xIn, int yIn)
{
    switch (key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
        case ' ':
            pause = !pause;
            break;
        case 'w'://move forwards
            eye[0] += 0.1;
            break;
        case 's'://move back
            eye [0] -= 0.1;
            break;
        case 'a'://move left
            eye[2] += 0.1;
            break;
        case 'd': // move camera right
            eye[2] -= 0.1;
            break;
        case 'r': //reset the map
            terrain = map(H,0,0);
            terrain.setVoronoi();
            terrain.initMap();
            terrain.setMesh();
            terrain.initTextures();
            over.updateMap(terrain);
            break;
    }
}

//function to handle special keys
void special(int key, int x, int y){
    /* Camera movements set up here */
    switch(key){
        case GLUT_KEY_UP: //move along xz
            eye[0] += .0001*lookAt[0];
            eye[2] += .0001*lookAt[2];
            break;
        case GLUT_KEY_DOWN: //move along xz
            eye[0] -= .0001*lookAt[0];
            eye[2] -= .0001*lookAt[2];
            break;
    }
}

//display function, draws all of the biomes
void display(void)
{
  glClearColor(0.15,0.45,0.75,0.65); // this simulates a sky colour
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  setEyeHeight();
  gluLookAt(eye[0], eye[1], eye[2], lookAt[0], lookAt[1], lookAt[2], up[0], up[1], up[2]);

  if (eye[1] < 1){
    density = 0.03;
    fogColor[1] = 0.2;
    fogColor[0] = 0.2;
    fogColor[2] = 0.8;
    glFogi (GL_FOG_MODE, GL_EXP); //sets up fog
  }
  else{
    density = 0.01;
    fogColor[0] = 0.5;
    fogColor[1] = 0.5;
    fogColor[2] = 0.5;
    glFogi (GL_FOG_MODE, GL_EXP2);
  }
  glFogfv (GL_FOG_COLOR, fogColor);
  glFogf (GL_FOG_DENSITY, density);

  light(); //turns on lighting
  terrain.drawMap();
  glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);

  glDisable(GL_TEXTURE_2D);
  glColor3f(0,0,0);
    glDrawPixels( H*2, H*2, GL_RGB, GL_UNSIGNED_INT, data );
  glEnable(GL_TEXTURE_2D); //enables texturing
  glPopMatrix();
	glutSwapBuffers(); // double buffering

}

//timer function, for smoother animations
void FPS(int val){
    if (pause){
        glutPostRedisplay();

    }
    glutTimerFunc(17, FPS, 0);
}

//function that is called back during the functions main loop telling glut what functions to use for different events
void callBackInit(){
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
  glutReshapeFunc(handleReshape);
  glutSpecialFunc(special);
  glutPassiveMotionFunc(passive);
  glutTimerFunc(0, FPS, 0);
}

//sets up projection and the camera
void projection(){
    /*Let's set up the projection here!*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
    glEnable(GL_NORMALIZE);
   //glOrtho(-10,10,-10,10,-10,10);
   // glFrustum(-10,10,-10,10,5,10);
    gluPerspective(45,1,1,400);
}

//main function where all our code is run
int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(1360, 720);
	glutInitWindowPosition(0, 0);

  srand(time(NULL));

	WindowID1 = glutCreateWindow("project");
	callBackInit();

  projection();

  glutSetCursor(GLUT_CURSOR_CROSSHAIR); //turns cursor into a crosshair

  //initializes the terrain
  terrain.setVoronoi();
  terrain.initMap();
  terrain.initTextures();
  terrain.setMesh();

  //updates the overhead
  over.updateMap(terrain);
  setData();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);

  glCullFace(GL_BACK);
  glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return(0);
}
