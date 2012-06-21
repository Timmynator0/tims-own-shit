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
#define TEXTURE_COUNT 1

GLuint textures[TEXTURE_COUNT];
const char *TextureFiles[TEXTURE_COUNT] = {"rock1.tga"};
	//"wood.tga","sand.tga","glass.tga","tree.tga","leaves.tga"};

int screenwidth= 1024, screenheight = 700;
bool isTextureLoaded = 0;

vector<block> blocks;
// angle of rotation for the camera direction
float angle = 0.0f;

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
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

		if (deltaMove)
		computePos(deltaMove);
        glutSwapBuffers();
	

		if(!isTextureLoaded)
	{
		isTextureLoaded = true;
		// het laden van de texture voor de achtergrond
		glGenTextures(TEXTURE_COUNT, textures);
		for(int i= 0; i < TEXTURE_COUNT; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			printf("loading %s\n",TextureFiles[i]);
			LoadTGATexture(TextureFiles[i], GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
		}

	}	


	

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx, y,  z+lz,
			0.0f, y,  0.0f);

// Draw ground

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();


		blocks.push_back(block(1,0,0,0));
	//for(int i = 0; i < blocks.size(); i++)
//	{
		glBindTexture(GL_TEXTURE_2D,textures[blocks[0].type]);
		blocks[0].draw();//
	//}
	
} 

void processNormalKeys(unsigned char key, int xx, int yy) { 

	 switch (key) {
             case 'q' : y++; break;
             case 'z' : y--; break;
			 case 27 : exit(0);
       }
        
} 

void pressKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
			
       }
} 

void releaseKey(int key, int x, int y) { 	

        switch (key) {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
} 

void mouseMove(int x, int y) { 	
	//int tempx = 0;
      
	// this will only be true when the left button is down
	
	if (xOrigin >= 0) {
	
	 if(!warped)
    {
		// update deltaAngle
	//	deltaAngle = (x - xOrigin) * 0.001f;

		// update camera's direction
	//	lx = sin(angle + deltaAngle);
	//	lz = -cos(angle + deltaAngle);
		
		lx=( float)(x - glutGet(GLUT_WINDOW_WIDTH)/2); 


		//glutWarpPointer(deltaAngle,yOrigin);
		warped=true;
		glutWarpPointer(glutGet(GLUT_WINDOW_X)+glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_Y)+glutGet(GLUT_WINDOW_HEIGHT)/2);
		//SetCursorPos(xOrigin,yOrigin);
	}
	else
	{
			warped = false ;
			
	}	
	 glutPostRedisplay();
 }
	 
		 
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(screenwidth, screenheight);
	glutCreateWindow("bake cookies");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glutSetCursor(GLUT_CURSOR_NONE); 
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}