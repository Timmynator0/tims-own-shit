#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include "BramsPrimitives.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "loadTGA.h"
#include "ObjModel.h"
#include "block.h"
#define TEXTURE_COUNT 2

//GLuint textures[TEXTURE_COUNT];
//const char *TextureFiles[TEXTURE_COUNT] = {"rock1.tga"};
	//"wood.tga","sand.tga","glass.tga","tree.tga","leaves.tga"};

int screenwidth= 1024, screenheight = 700;
bool isTextureLoaded = 0;
vector<ObjModel*> models;

vector<block> blocks;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, y= 6.0f, z=5.0f ;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1, yOrigin = -1;
bool warped = true;
float xrottemp =0,yrottemp = 0;
//angle of rotation + positions
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float cRadius = 10.0f; // our radius distance from our character

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positionx[10];

//vector<Vec3f> *vertices;



void cubepositions (void) { //set the positions of the cubes
	for (int i=0;i<10;i++)
	{
	positionz[i] = rand()%5 + 1;
	positionx[i] = rand()%5 + 1;
	}
}

//draw the cube
void cube (void) {
	for (int i=0;i<10 - 1;i++)
	{
	glPushMatrix();
	glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10); //translate the cube
	glutSolidCube(2); //draw the cube
	glPopMatrix();
	}
}

void floor(void)
{
	
	unsigned int GridSizeX = 16;
	unsigned int GridSizeY = 16;
	unsigned int SizeX = 8;
	unsigned int SizeY = 8;
	
	glPushMatrix();
	glTranslated(-positionx[1] * 10,-1, -positionz[1] * 10);
	glRotatef(90,1.0,0.0,0.0);
	glBegin(GL_QUADS);
	for (unsigned int x =0;x<GridSizeX;++x)
		for (unsigned int y =0;y<GridSizeY;++y)
		{
			if ((x+y)& 0x00000001) //modulo 2
				glColor3f(1.0f,1.0f,1.0f); //white
			else
				glColor3f(0.0f,0.0f,0.0f); //black
 
			glVertex2f(    x*SizeX,    y*SizeY);
			glVertex2f((x+1)*SizeX,    y*SizeY);
			glVertex2f((x+1)*SizeX,(y+1)*SizeY);
			glVertex2f(    x*SizeX,(y+1)*SizeY);
 
		}
	glEnd();
	glPopMatrix();
}

void loadModels()
{
	models.push_back(new ObjModel("models/world4export.obj"));
	models.push_back(new ObjModel("models/steve.obj"));
}

void init (void) {
	xpos = -31;
	zpos = -31;
	yrot = 140;
	cubepositions();
	loadModels();
}

void enable (void) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void drawWorld()
{
	glPushMatrix();
	//glTranslated(-positionx[1] * 10,-8.5, -positionz[1] * 10);
	glTranslated(0 ,-8.5, 0);
	models[0]->draw();
	glPopMatrix();
}

void drawPlayer()
{
	glTranslatef(0.0f, 0.0f, -cRadius);
	glRotated(xrot,1.0,0.0,0.0);
	
	
	models[1]->draw();


	glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos,0.0f,-zpos); //translate the screen to the position of our camera
	std::cout << xpos << ",," << zpos << std::endl;
	//glColor3f(1.0f, 0.0f, 0.0f);
	
	//glutSolidCube(3); //Our character to follow
	
}

void display (void) {
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	
    
	glLoadIdentity(); 
	
	drawPlayer(); //draw the player in front of the camera
	
	drawWorld(); 	// the world
	


	glutSwapBuffers(); //swap the buffers
	angle++; //increase the angle
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode (GL_PROJECTION); //set the matrix to projection
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); //set the perspective (angle of sight, width, height, , depth)
	glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void keyboard (unsigned char key, int x, int y) {
	if (key=='q')
	{
		if(xrot <= 90)
		{
			xrot += 1;
		}
		if (xrot >360) 
		{
			xrot -= 360;
		}
	
		
	}

	if (key=='z')
	{
		if(xrot >= 0)
		{
			xrot -= 1;
		}
		if (xrot < -360) 
		{
			xrot += 360;
		}
	}

	if (key=='w')
	{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f); 
	xpos += float(sin(yrotrad));
	zpos -= float(cos(yrotrad));
	ypos -= float(sin(xrotrad));
	}

	if (key=='s')
	{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f); 
	xpos -= float(sin(yrotrad));
	zpos += float(cos(yrotrad));
	ypos += float(sin(xrotrad));
	}

	if (key=='d')
	{
    float yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xpos += float(cos(yrotrad)) * 0.2;
	zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key=='a')
	{
	float yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xpos -= float(cos(yrotrad)) * 0.2;
	zpos -= float(sin(yrotrad)) * 0.2;
	}

	if (key==27)
	{
	exit(0);
	}
	if (key==' ')
	{

		//std::cout << "space has been pressed" << std::endl;
	}
}

void mouseMovement(int x, int y) {
	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	//std::cout << "diffy = "<<x<< std::endl;
	//std::cout << "diffx = "<<y<< std::endl;




	xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
	//std::cout << "x rotation "<<xrot<< std::endl;
	yrot += (float) diffx;	//set the yrot to yrot with the addition of the difference in the x position

	//check for unuseable angles
	if(xrot < 0)
	{
		xrot = 0;
		
	}
	if(xrot > 90)
	{
		xrot = 90;
		
	}
	
	// meh, backup?
		/*if(xrot >= 0 && xrot <= 90)
		{
			glRotatef(xrot,1.0,0.0,0.0);
		}
	if(xrot < 0)
	{
		xrot = 0;
		glRotated(xrot,1.0,0.0,0.0);
	}
	if(xrot > 90)
	{
		xrot = 90;
		glRotated(xrot,1.0,0.0,0.0);
	}*/

}

int main (int argc, char **argv) 
{
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window"); 
	enable();
	init (); 
    glutDisplayFunc (display); 
	glutIdleFunc (display); 
	glutReshapeFunc (reshape); 

	glutPassiveMotionFunc(mouseMovement); //check for mouse movement

	glutKeyboardFunc(keyboard); 
    glutMainLoop(); 
    return 0;
}
