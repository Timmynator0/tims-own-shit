#pragma
#ifndef BLOCK
#define BLOCK
#include "loadTGA.h"



class block{

public :
	int	type;
	float blockX;
	float blockY;
	float blockZ;
	bool placed;
	block();
	block(int Type, float BlockX, float BlockY, float BlockZ);
	void draw();
};

#endif BLOCK