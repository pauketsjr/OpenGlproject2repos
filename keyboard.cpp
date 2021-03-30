#include "GameManager.h"
#include "PlayerManager.h"
#include "MenuManager.h"
#include "ScoreManager.h"

extern ScoreManager score;
extern MenuManager menu;
extern PlayerManager player;

void iG::iKeyboard(unsigned char key)
{
	switch (menu.get())
	{
	case MenuManager::MAIN:
		switch (key)
		{
		case 'q':
			glutLeaveMainLoop();
			break;
		case '\r':
			menu.keyEnter();
			break;
		}
		break;
	case MenuManager::PLAY:
		switch (key)
		{
		case '\b':
			menu.set(MenuManager::MAIN);
			PlaySoundA(NULL, NULL,NULL);
			break;
		}
		break;
	case MenuManager::SCORE:
		switch (key)
		{
		case '\b':
			menu.set(MenuManager::MAIN);
			break;
		case 'd':
			score.erase();
			break;
		case 'e':
			score.edit();
			break;
		}
		break;
	case MenuManager::GAMEOVER:
		score.nameEntry(key);
		break;
	}
}

void iG::iSpecialKeyboard(unsigned char key)
{
	switch (menu.get())
	{
	case MenuManager::MAIN:
		switch (key)
		{
		case GLUT_KEY_UP:
			menu.keyUp();
			break;
		case GLUT_KEY_DOWN:
			menu.keyDown();
			break;
		}

	case MenuManager::PLAY:
		switch (key)
		{
		case GLUT_KEY_UP:
			player.moveUp();
			break;
		case GLUT_KEY_DOWN:
			player.moveDown();
			break;
		case GLUT_KEY_LEFT:
			player.moveLeft();
			break;
		case GLUT_KEY_RIGHT:
			player.moveRight();
			break;
		case GLUT_KEY_END:
			menu.set(MenuManager::MAIN);
			break;
		}
		break;
	case MenuManager::SCORE:
		switch (key)
		{
		case GLUT_KEY_UP:
			score.keyUp();
			break;
		case GLUT_KEY_DOWN:
			score.keyDown();
			break;
		}
	}	
}
