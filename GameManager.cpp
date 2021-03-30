#include "GameManager.h"
#include "LevelManager.h"
#include "TilesManager.h"
#include "CameraManager.h"
#include "PlayerManager.h"
#include "ScoreManager.h"
#include "MenuManager.h"
#include "Opengl\\include\\stb_image.h"
extern MenuManager menu;
extern ScoreManager score;
extern PlayerManager player;
extern CameraManager camera;
extern LevelManager level;
extern TilesManager tiles;
GameManager::GameManager()
{
	timer = 0;
}
void GameManager::init()
{
	level.init();
	tiles.init();
	player.init();
	camera.init();
}
void GameManager::set()
{
	if (level.levelUp())
	{
		level.set();  
		tiles.set();
		player.set();
		camera.set();
	}
	else
	{
		PlaySoundA(NULL, NULL, NULL);
		menu.set(MenuManager::GAMEOVER);	// Player finished the game
	}
}

void GameManager::reset()
{
	timer = 0;
	level.reset();
	score.reset();
	player.reset();
}

void GameManager::incTimer()
{
	timer+=.03;
}

void GameManager::drawTime()
{
	char temp[40];
	snprintf(temp, 40, "TIME :  %.0f", timer);
	iG::iSetColor(RED);
	iG::iText(iG::iGetWindowWidth() - 200.0f, iG::iGetWindowHeight() - 200.0f, temp);
}

GLfloat GameManager::getTime()
{
	return timer;
}