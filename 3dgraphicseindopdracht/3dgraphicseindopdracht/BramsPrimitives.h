#ifndef BPRIMITIVES
#define BPRIMITIVES

#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/freeglut.h>            // Windows FreeGlut equivalent
#endif

const long double PI = acos((long double) -1);

/* This method creates a cube at X,Y,Z, with width,height,depth and with center at x, y+height,z+depth,
 * param u,v are meant for starting position @ the texture, uvsize is the size of x in the texture
*/
void createDiamondCube(float x, float y, float z);
void createPentagon(float x, float y, float z);
void createTriangle(float x, float y, float z);
void createCube(float width, float height, float depth,float u, float v, float uvsize);
void createPyramid(float width, float height, float depth,float u, float v, float uvsize);
void createCircle(float radiusx, float radiusy, int segments,int part,bool texture, float u, float v, float uvsize);
void createCylinder(float radiusx, float radiusy, int segments, float depth,int part, bool texture,float u, float v, float uvsize);


#endif