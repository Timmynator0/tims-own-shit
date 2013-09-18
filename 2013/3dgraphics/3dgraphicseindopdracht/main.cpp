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
#include <math.h>       /* atan */

#define PI 3.14159265
#define TEXTURE_COUNT 12

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


//angle of rotation + positions
float xpos = 0, ypos = 0, zpos = 0, xrot = 8, yrot = 0;

// our radius distance from our character
float cRadius = 10.0f; 

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positionx[10];

//vector<Vec3f> *vertices;


//jumping params
float MaxJump=1.7; // max height of jump
float Gravity=1.05; // manipulates max jump
float SubMaxJump= MaxJump; //constant that restores MaxJump
float y2=0; // Y position
float yOrigin = y2; // Constant that restores y back to it's origin
bool Jumping=false; //Jumping flag
bool Falling=false; //Falling flag
bool JumpOK=true; //Is it okay to jump?
bool spacerelease = true;
bool wPressed , sPressed, qPressed, zPressed = false;




void cubepositions (void) { //set the positions of the cubes
	for (int i=0;i<10;i++)
	{
	positionz[i] = rand()%5 + 1;
	positionx[i] = rand()%5 + 1;
	}
}

//draw the cube
void cube(void) {
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
	//models.push_back(new ObjModel("models/world4export.obj"));
	models.push_back(new ObjModel("models/world3.obj"));
	models.push_back(new ObjModel("models/steve.obj"));
	models.push_back(new ObjModel("models/sun.obj"));
	models.push_back(new ObjModel("models/kip.obj"));
	models.push_back(new ObjModel("models/sphere.obj"));
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
	//glEnable(GL_LIGHT1);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_AUTO_NORMAL);
	//LIGHTINGGG
	//GLfloat light_diffuse[] = { 255, 244 , 150, 0 }; // = { 255, 244 , 196, 1 }; 
	//GLfloat pos[] = { 0, 20 , -0, 1 };

	//glLightfv(GL_LIGHT1, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
	//glLightf(GL_LIGHT1, GL_POSITION, *pos);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_EMISSION);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glShadeModel (GL_SMOOTH); //set the shader to smooth shader
}

void handleJump()
{

/*If you're jumping, divide MaxJump by Gravity so it will slowly get smaller, and add MaxJump to y so the character moves up*/

if(Jumping)
{
	if(wPressed)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f); 
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}
	if(sPressed)
	{
			float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f); 
	xpos -= float(sin(yrotrad));
	zpos += float(cos(yrotrad));
	ypos += float(sin(xrotrad));
	}

    MaxJump /= Gravity;
    ypos += MaxJump;
}
 
/*If MaxJump has run out, our character is no longer jumping, but falling*/
if(MaxJump <= 1)
{
    Falling=true;
    Jumping=false;
}
 
/*Opposite of Jumping*/
if(Falling)
{
	if(wPressed)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f); 
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}
	if (sPressed)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f); 
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

    MaxJump *= Gravity;
    ypos -= MaxJump;
}
 
/*Keeps MaxJump from getting higher than 4, so the character doesn't fall at large intervals.*/
if(Falling && MaxJump > 4)
{
	MaxJump = 4;
}
/*If the block is back to it's y origin, make both jumping and falling false, and assign MaxJump to constant SubMaxJump to restore it back to normal. It's not okay to jump again unless you release the UP key, and then press it again.*/
	if(ypos <= yOrigin )
	{
		Jumping=false;
		Falling=false;
		MaxJump=SubMaxJump;
		if (spacerelease)
		{
			JumpOK=true;
		}
		ypos = yOrigin;
	}
	if(!Jumping && !Falling && ypos >= yOrigin)
	{
		ypos = yOrigin;
	}
}



void drawWorld()
{
	glPushMatrix();
	glTranslatef(0 ,-16.4, 0);
	models[0]->draw();
	glPopMatrix();
}

void drawPlayer()
{
	glTranslatef(0.0f, 0.0f, -cRadius);
	glRotated(xrot,1.0, 0.0 ,0.0);

	models[1]->draw();

	std::cout << xrot << std::endl;
	glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera

}


float planetorb  = 1;
void drawSun()
{
	glPushMatrix();
	
	glTranslatef(0, 20 , -0);
	glRotatef(planetorb,0.0,0.0,1.0); // orbits the planet.
    glTranslatef(110,0.0,0.0);        // sets the radius of the orbit 
	models[2]->draw();
	
	if(qPressed)
	{
		planetorb ++;
		planetorb ++;
	}
	else if(zPressed)
	{
		planetorb --;
		planetorb --;
	}

  glPopMatrix();
}

float chickenX = 0.0f, chickenY = -23.1f, chickenZ = 0.0f;
double diffY= 0, diffX = 0;
void drawChicken() // just a cube
{

	glPushMatrix();
	
	//checks if chicken is in range, if not, move him towards the player
	int radius = 5 ; // the radius in which the chicken should not move
	//move chicken to the left
//	for(int ii = 0 ; ii < radius ; ii++)
//	{
		if(chickenX > xpos + radius)
		{
			chickenX -= 0.5f;
		}
		if(chickenX < xpos - radius)
		{
			chickenX += 0.5f;
		}
		if(chickenZ > zpos + radius)
		{
			chickenZ -= 0.5f;
		}
		if(chickenZ < zpos - radius)
		{
			chickenZ += 0.5f;
		}


	float angle = atan2(xpos - chickenX, zpos - chickenZ);
	//Of course the return type is in radians, if you need it in degrees just do angle * 180 / PI
	glTranslatef(chickenX, chickenY, chickenZ);
	glRotatef( angle* 180 / PI ,0.0,1,0.0); 
	models[3]->draw(); // draw the chicken!!
		
	glPopMatrix();

}
void drawEnv()
{
	glPushMatrix();
	glTranslatef(0, 40 ,-0);
	glRotatef(95,0,1,0);
	models[4]->draw();



	glPopMatrix();
}
void display (void) 
{
	
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    
	glLoadIdentity(); 
	

	handleJump();

	drawPlayer();	 //draw the player in front of the camera	
	drawWorld(); 	// the world
	drawChicken();
	drawSun();
	drawEnv();


	glutSwapBuffers(); //swap the buffers
	

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
		qPressed = true; 
	}

	if (key=='z')
	{
		zPressed = true;
	}

	if (key=='w')
	{
		wPressed = true;
		if(!Jumping)
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f); 
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}
		
	}

	if (key=='s')
	{

		sPressed = true;
		if(!Jumping)
		{
	float xrotrad, yrotrad;
	yrotrad = (yrot / 180 * 3.141592654f);
	xrotrad = (xrot / 180 * 3.141592654f); 
	xpos -= float(sin(yrotrad));
	zpos += float(cos(yrotrad));
	ypos += float(sin(xrotrad));
		}
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

	if (key==27)// esc key :3
	{
	exit(0);
	}

	if (key ==' ')
	{
		
		spacerelease = false;
		Jumping = true; // you are now jumping, you can't jump again until jump is done!
		JumpOK=false; 
		std::cout << "space has been pressed" << std::endl;
	}
}

void keyboardUp(unsigned char key, int x, int y)

{
	if (key =='q')
	{
		qPressed = false;
	}
	if (key =='z')
	{
		zPressed = false;
	}
	if (key ==' ')
	{
		//Jumping = true; // you are now jumping, you can't jump again until jump is done!
		//JumpOK=true;
		spacerelease = true;
		//std::cout << "space has been pressed" << std::endl;
	}
	if ( key == 'w')
	{
		wPressed = false;
	}
	if(key = 's')
	{
		sPressed = false;
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
	if(xrot < 1)
	{
		xrot = 1;
		
	}
	if(xrot > 90)
	{
		xrot = 90;
		
	}
	//cout << xrot << std::endl;
}

void idle()
{
	Sleep(1);
	glutPostRedisplay();
}
int main (int argc, char **argv) 
{
    glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window"); 
	enable();
	init (); 
    glutDisplayFunc (display); 
	glutIdleFunc (idle); 
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc (reshape); 
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutKeyboardFunc(keyboard); 
    glutMainLoop(); 
    return 0;
}
