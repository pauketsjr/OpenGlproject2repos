#ifndef __SPIKES_MANAGER__
#define __SPIKES_MANAGER__
#include "Spike.h"
#include "GameManager.h"
class SpikesManager
{
	vector<Spike> s;	
	unsigned char* image;
	int imageWidth, imageHeight;
public:
	SpikesManager();
	~SpikesManager();
	void addSpike(GLfloat,GLfloat);
	void update();	// Moving spikes
	void draw();
	bool checkCollision();
	void clear();
};
#endif
