#include <iostream>
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <cmath>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include "loadTGA.h"
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#define FREEGLUT
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

bool textureloaded = false;

bool getTextureLoaded(){
	return textureloaded;
}

GLbyte *LoadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat) 
{ 
	FILE *pFile; // File pointer 
	TGAHEADER tgaHeader; // TGA file header 
	unsigned long lImageSize; // Size in bytes of image 
	short sDepth; // Pixel depth; 

	GLbyte *pBits = NULL; // Pointer to bits 
	// Default/Failed values 
	*iWidth = 0; 
	*iHeight = 0; 
	*eFormat = GL_RGB; 
	*iComponents = GL_RGB; 

	// Attempt to open the file 
	pFile = fopen(szFileName, "rb"); 
	if(pFile == NULL) 
		return NULL; 

	// Read in header (binary) 
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian 
	#ifdef __APPLE__ 
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart); 
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength); 
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart); 
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart); 
	LITTLE_ENDIAN_WORD(&tgaHeader.width); 
	LITTLE_ENDIAN_WORD(&tgaHeader.height); 
	#endif 

	// Get width, height, and depth of texture 
	*iWidth = tgaHeader.width; 
	*iHeight = tgaHeader.height; 
	sDepth = tgaHeader.bits / 8; 


	// Put some validity checks here. Very simply, I only understand 
	// or care about 8, 24, or 32 bit targa’s. 
	if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32) return NULL; 

	// Calculate size of image buffer 
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth; 


	// Allocate memory and check for success 
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte)); 
	if(pBits == NULL)	return NULL; 

	// Read in the bits 
	// Check for read error. This should catch RLE or other 
	// weird formats that I don’t want to recognize 
	if(fread(pBits, lImageSize, 1, pFile) != 1) 
	{ 
		free(pBits); 
		return NULL; 
	} 


	// Set OpenGL format expected 
	switch(sDepth) 
	{ 
	case 3: // Most likely case
		#ifndef OPENGL_ES 
		*eFormat = GL_BGR; 
		*iComponents = GL_RGB; 
		#endif 
		#ifdef WIN32  
		*eFormat = GL_BGR; 
		*iComponents = GL_RGB; 
		#endif 
		#ifdef linux 
		*eFormat = GL_BGR; 
		*iComponents = GL_RGB; 
		#endif 
		break; 

	case 4: 
	*eFormat = GL_BGRA; 
	*iComponents = GL_RGBA; 
	break; 


	case 1: 
	*eFormat = GL_LUMINANCE; 
	*iComponents = GL_LUMINANCE; 
	break; 
	default: // RGB 


	// If on the iPhone, TGA’s are BGR, and the iPhone does not 
	// support BGR without alpha, but it does support RGB, 
	// so a simple swizzle of the red and blue bytes will suffice. 
	// For faster iPhone loads however, save your TGA’s with an Alpha! 

	#ifdef OPENGL_ES 

	for(int i = 0; i < lImageSize; i+=3) 
	{ 
	GLbyte temp = pBits[i]; 
	pBits[i] = pBits[i+2]; 


	pBits[i+2] = temp; 
	} 
	#endif 
	break; 
	} 

	// Done with File 
	fclose(pFile); 
	// Return pointer to image data 
	return pBits; 
} 
// Load a TGA as a 2D Texture. Completely initialize the state
bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;
	
	// Read the texture bits
	pBits = LoadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	//std::cout << "pbi: "<<pBits<<" a" <<std::endl;
	if(pBits == NULL){ 
		free(pBits);
		textureloaded = false;
		return false;
	}else {
		textureloaded = true;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
				 eFormat, GL_UNSIGNED_BYTE, pBits);
	
    free(pBits);
    
   /* if(minFilter == GL_LINEAR_MIPMAP_LINEAR || 
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
        glGenerateMipmap(GL_TEXTURE_2D);
    */
	return true;
}