#include "SpikesManager.h"
#include "Spike.h"
#include "TilesManager.h"
#include "PlayerManager.h"
#include "Opengl\\include\\stb_image.h"
extern PlayerManager player;
extern TilesManager tiles;
SpikesManager::SpikesManager()
{
	int n;
	image = stbi_load("Data\\Image\\spikes.png", &imageWidth, &imageHeight, &n, 4);
}
SpikesManager::~SpikesManager()
{
	stbi_image_free(image);
}
void SpikesManager::addSpike(GLfloat x,GLfloat y)
{
	Spike temp;
	temp.init();
	temp.setCenter(x, y);
	temp.setHeight(tiles.getHeight());
	temp.setWidth(tiles.getWidth());
	s.push_back(temp);
}
void SpikesManager::update()
{
	for (GLint i=0;i<s.size();i++)
	{
		s[i].update();
	}
}
void SpikesManager::clear()
{
	s.clear();
}
bool SpikesManager::checkCollision()
{
	for (GLint i = 0;i < s.size();i++)
	{
		if (floor(player.getY()/player.getHeight())==floor(s[i].getY() / s[i].getHeight())|| ceil(player.getY() / player.getHeight()) == floor(s[i].getY() / s[i].getHeight()))
		{
			if (s[i].getX() + s[i].getWidth() >= player.getX() && s[i].getX() + s[i].getWidth() <= player.getX() + player.getWidth())
			{
				return true;
			}
			else if (player.getX() + player.getWidth() >= s[i].getX() && player.getX() + player.getWidth() <= s[i].getX() + s[i].getWidth())
			{
				return true;
			}
		}
	}
	return false;
}
void SpikesManager::draw()
{
	for (auto i : s)
	{
		//iG::iSetColor(BLUE);
		//iG::iRectangle(i.getX()- tiles.offsetCols * tiles.getWidth(), i.getY()- tiles.offsetRows * tiles.getHeight(), tiles.getWidth(), tiles.getHeight());
		iG::iShowImage(i.getX() - tiles.offsetCols * tiles.getWidth(), i.getY() - tiles.offsetRows * tiles.getHeight(), imageWidth, imageHeight,image);
	}
}