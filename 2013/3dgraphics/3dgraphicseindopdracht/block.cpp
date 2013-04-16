#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include "loadTGA.h"
#include "ObjModel.h"
#include "block.h"
#include "BramsPrimitives.h"
#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT 
#include <GL/freeglut.h>// Windows FreeGlut equivalent
#endif

block::block(int Type, float BlockX, float BlockY, float BlockZ)
{
	type = Type;
	blockX = BlockX;
	blockY = BlockY;
	blockZ = BlockZ;
	placed = false;
}

void block::draw()
{
	int x = 5;
	int y = 5;
	int z = 5;
	//glEnable(GL_TEXTURES_2D);
	//glBindTextures(GL_TEXTURE_2D,textures[1]);
//	blockX = x;
//	blockY = y;
//	blockZ = z;
	glBegin(GL_QUADS);
		//begin cube
		//zijkant links
		glTexCoord2f(1,1);	glVertex3f(x-2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x-2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z+2.5f);

		//zijkant rechts
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x+2.5f,0.0f,z+2.5f);

		//zijkant zuid
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z-2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z-2.5f);

		//zijkant noord
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,0.0f,z+2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,0.0f,z+2.5f);

		//bovenkant crate
		glTexCoord2f(1,1);	glVertex3f(x+2.5f,y,z-2.5f);
		glTexCoord2f(1,0);	glVertex3f(x+2.5f,y,z+2.5f);
		glTexCoord2f(0,0);	glVertex3f(x-2.5f,y,z+2.5f);
		glTexCoord2f(0,1);	glVertex3f(x-2.5f,y,z-2.5f);

		glEnd();


	//	glBegin(GL_TRIANGLE_STRIP);
	//glTexCoord2f(1,1);							glVertex3f(-x,-y,-z);		//1
	//glTexCoord2f(1,0);		glVertex3f(x,-y,-z);		//2
	//glTexCoord2f(0,0);			glVertex3f(-x,-y,z);			//3
	//glTexCoord2f(0,1);		glVertex3f(x,-y,z);			//4

	//glTexCoord2f(1,1);			glVertex3f(-x,y,z);			//5
	//glTexCoord2f(0,0);		glVertex3f(x,y,z);			//6
	//glTexCoord2f(0,0);			glVertex3f(-x,y,-z);			//7
	//glTexCoord2f(0,1);			glVertex3f(x,y,-z);			//8
	//glEnd();

	//glBegin(GL_TRIANGLE_STRIP);
	//glTexCoord2f(1,1);			glVertex3f(-x,-y,z);			//3
	//glTexCoord2f(1,0);			glVertex3f(-x,y,z);			//5
	//glTexCoord2f(0,0);			glVertex3f(-x,-y,-z);		//1
	//glTexCoord2f(0,1);			glVertex3f(-x,y,-z);			//7

	//glTexCoord2f(1,1);			glVertex3f(x,-y,-z);		//2
	//glTexCoord2f(1,0);			glVertex3f(x,y,-z);			//8
	//glTexCoord2f(0,0);			glVertex3f(x,-y,z);			//4
	//glTexCoord2f(0,1);			glVertex3f(x,y,z);			//6
	//glEnd();

}