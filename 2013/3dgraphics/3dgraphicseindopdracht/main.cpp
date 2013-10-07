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
#include <math.h>    
#include <string>
#include <sstream>


#define PI 3.14159265
#define TEXTURE_COUNT 12



int screenwidth= 1366, screenheight = 768;
bool isTextureLoaded = 0;

vector<ObjModel*> models;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, y= 6.0f, z=5.0f ;


//angle of rotation + positions
float xpos = 0, ypos = 0, zpos = 0, xrot = 8, yrot = 0;

// our radius distance from our character
float cRadius = 10.0f; 
//x and Y positions for the mousemovement, so we know where the mouse was lasttime.
float lastx, lasty;


//jumping params
float MaxJump=1.7; // max height of jump
float Gravity=1.05; // manipulates max jump
float SubMaxJump= MaxJump; //constant that restores MaxJump
float y2= 0; // Y position
float yOrigin = y2; // Constant that restores y back to it's origin
bool Jumping=false; //Jumping flag
bool Falling=false; //Falling flag
bool JumpOK=true; //Is it okay to jump?
bool spacerelease = true;
bool wPressed , sPressed, qPressed, zPressed = false;

//var for the size of the planetary orbitation of the "sun"
float planetorb  = 1;

void loadModels()
{

	models.push_back(new ObjModel("models/world3.obj"));
	models.push_back(new ObjModel("models/steve.obj"));
	models.push_back(new ObjModel("models/sun.obj"));
	models.push_back(new ObjModel("models/kip.obj"));
	models.push_back(new ObjModel("models/sphere2.obj"));
}

void init (void) {
	xpos = -31;
	zpos = -31;
	yrot = 140;
	loadModels();
}

void enable (void) {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

//	glEnable(GL_COLOR_MATERIAL);
//	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;





	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glShadeModel (GL_SMOOTH); //set the shader to smooth shader



}

void handleJump()
{

/*If you're jumping, divide MaxJump by Gravity so it will slowly get smaller, and add MaxJump to y so the character moves up*/

if(Jumping)
{ 
	//code so whenver we are jumping, we can still move forward.
	// this to enable the player to jump forward and backwards
	

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
 
//if MaxJump has run out, our character is no longer jumping, but falling
if(MaxJump <= 1)
{
    Falling=true;
    Jumping=false;
}
 
//Opposite of Jumping
if(Falling)
{
	// stil able to fall "backwards"
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
 
//Keeps MaxJump from getting higher than 4, so the character doesn't fall at large intervals
if(Falling && MaxJump > 4)
{
	MaxJump = 4;
}
/*If the player is back to it's y origin, 
make both jumping and falling false, and assign MaxJump to constant SubMaxJump 
to restore it back to normal. */
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
	glTranslatef(0 ,-16.4, 0);// -16.4 is to place the world exacly beneath the player.
	models[0]->draw(); // draw the world model.
	glPopMatrix();
}

void drawPlayer()
{
	glTranslatef(0.0f, 0.0f, -cRadius); // distance from player
	glRotated(xrot,1.0, 0.0 ,0.0);		// rotation bases on mous
	models[1]->draw(); // draw the player model
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera

}

void drawSun()
{
	glPushMatrix();
	
	glTranslatef(0, 20 , -0);         // translate planet at a 20 height.
	
	glRotatef(planetorb,0.0,0.0,1.0); // orbits the planet.
    glTranslatef(110,0.0,0.0);        // sets the radius of the orbit 


	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0, 20, 0, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glDisable(GL_COLOR_MATERIAL);
	models[2]->draw();
	glEnable(GL_COLOR_MATERIAL);

	std::cout << "planetorb = "<<planetorb<< std::endl;
	if (planetorb > 360 )
	{
		planetorb = 0;
	}
	if(planetorb < 0)
	{
		planetorb = 360;
	}
	if(qPressed)
	{
		planetorb += 2;
		
	}
	else if(zPressed)
	{
		planetorb -= 2;
	
	}

	if(planetorb <= 320 && planetorb >= 200 )
	{	
		glDisable(GL_LIGHT0);
	}
	else
	{
		glEnable(GL_LIGHT0);
	}

  glPopMatrix();
}

float chickenX = 0.0f, chickenY = -23.1f, chickenZ = 0.0f;
double diffY= 0, diffX = 0;
void drawChicken() // just a cube
{

	glPushMatrix();
	
	//checks if chicken is in range, if not, move him towards the player
	int radius = 5 ; // the radius in which the chicken should not move ( the player needs his space!)

	//move chicken to the left (based on a 2d XZ coordinate map) 
		if(chickenX > xpos + radius)
		{
			chickenX -= 0.5f;
		}
		//move the chicken to the right
		if(chickenX < xpos - radius)
		{
			chickenX += 0.5f;
		}
		//move up
		if(chickenZ > zpos + radius)
		{
			chickenZ -= 0.5f;
		}
		//move down
		if(chickenZ < zpos - radius)
		{
			chickenZ += 0.5f;
		}
	glTranslatef(chickenX, chickenY, chickenZ); // actual movement of the chicken

	// determine the angle at which the chicken is moving, rotate him in that direction so he is facing the player.
	// Of course the return type is in radians, and I need it in degrees so we do angle * 180 / PI
	float angle = atan2(xpos - chickenX, zpos - chickenZ);		
	glRotatef( angle* 180 / PI ,0.0,1,0.0);  //actual rotating of the chicken
	models[3]->draw(); // draw the chicken!!
		
	glPopMatrix();

}
void drawEnv()
{


	glPushMatrix();
	glTranslatef(0, 40 ,-0); // place the spherical enviroment as 40height
	glRotatef(95,0,1,0);	// rotate it a bit so it looks more fancy 
	models[4]->draw();	// draw the sphere!
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
	drawChicken(); // handle the chicken!
	drawSun();		// sun handler
	drawEnv();		// build the spherical enviroment.



		// Create light components


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
		glutLeaveGameMode();
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

	if(x < 5) 
	{
		glutWarpPointer(screenwidth-10, y);
	}
	else if( x > screenwidth-5) 
	{
		glutWarpPointer(10,y);
	}

	int diffx=x-lastx; //check the difference between the current x and the last x position
	int diffy=y-lasty; //check the difference between the current y and the last y position
	lastx=x; //set lastx to the current x position
	lasty=y; //set lasty to the current y position
	//std::cout << "diffy = "<<x<< std::endl;
	//std::cout << "diffx = "<<y<< std::endl;




	xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
	//std::cout << "x rotation "<<xrot<< std::endl;
	yrot += (float) diffx;	//set the yrot to yrot with the addition of the difference in the x position

	//check for the allowed angles, +90 goes glitchy, en below 1 you are inside the floor, which is unpleasant.
	if(xrot < 1)
	{
		xrot = 1;
		
	}
	if(xrot > 90)
	{
		xrot = 90;
		
	}

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

	screenwidth = (float) GetSystemMetrics(0);
	screenheight = (float) GetSystemMetrics(1);

	stringstream ss;
	ss << screenwidth<<"x"<<screenheight<<":32@60";
	glutGameModeString( ss.str().c_str() ); //the settings for fullscreen mode	
	glutEnterGameMode();
	glutSetCursor(GLUT_CURSOR_NONE); // hide THA CURSOR!
	enable(); // set the glenables etc.
	init (); // load models and other things
    glutDisplayFunc (display); 
	glutIdleFunc (idle); 
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc (reshape); 
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutKeyboardFunc(keyboard); 
    glutMainLoop(); 
    return 0;
}
