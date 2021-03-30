#include "GameManager.h"
#include "PlayerManager.h"
#include "CameraManager.h"
#include "LevelManager.h"
#include "TilesManager.h"
#include "SpikesManager.h"
#include "MenuManager.h"
#include "ScoreManager.h"
#include "color.h"

ScoreManager score;
MenuManager menu;
SpikesManager spikes;
CameraManager camera;
PlayerManager player;
GameManager game;
LevelManager level;
TilesManager tiles;

void iG::windowSetup()
{
	// Setting bounds of pc screen
	iG::iSetScreenHeight(GetSystemMetrics(SM_CYFULLSCREEN));
	iG::iSetScreenWidth(GetSystemMetrics(SM_CXFULLSCREEN));

	// Setting position of game window
	iG::iSetWindowX(0);
	iG::iSetWindowY(0);

	// Setting game window bounds
	iG::iSetWindowHeight(iG::iGetScreenHeight());
	iG::iSetWindowWidth(iG::iGetScreenWidth());

	// Setting window background color
	iG::iSetBGColor(GREEN);
}

void update(GLint t)		// Game screen update
{
	if (menu.get() == MenuManager::PLAY)
	{
		game.incTimer();
		player.update();	// Updating Player position
		spikes.update();	// Updating Spikes position
		camera.update();	// Updating camera position
	}
	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

GLint main(GLint argc, char *argv[])
{
	glutInit(&argc, argv);	// Initializing glut
	iG::windowSetup();	// Setting window
	game.init();	// Initializing game
	iG::iInitialize("Game");	// Initializing proogram
	glutTimerFunc(30, update, 0);   // Registering timer callback
	glutMainLoop();		// Start program
	return 0;
}

	