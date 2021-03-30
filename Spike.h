#ifndef __SPIKE__
#define __SPIKE__
#include "Box.h"
class Spike:public Box
{
	GLfloat velX, centerX;
	GLfloat amplitude;	// Maximum distance from center
public:
	Spike();
	void init();
	void setCenter(GLfloat,GLfloat);
	void update();		// Move spike left and right
};
#endif

