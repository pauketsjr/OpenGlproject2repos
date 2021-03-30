#include "LevelManager.h"
#include "Color.h"
LevelManager::LevelManager()
{
	levelNum = totalLevels = 0;
	cols = rows = 0;
	startR = startC = endR = endC = 0;
	levelField = NULL;
}
LevelManager::~LevelManager()
{
	// Deallocating memory
	for (GLint i = 0; i < rows; i++)
	{
		delete[] levelField[i];
	}
	delete[] levelField;
}
void LevelManager::init()
{
	totalLevels = 2;
}
void LevelManager::setTotalLevels(GLint n)
{
	totalLevels = n;
}

void LevelManager::set()
{
	ifstream in(levels[levelNum], ios::in);
	if (!in)
	{
		cout << "File Reading error" << endl;
		return;
	}
	in >> rows >> cols;
	in >> startR >> startC;
	in >> endR >> endC;

	// Allocating memory
	levelField = new char* [rows];
	for (GLint i = 0; i < rows; i++)
	{
		levelField[i] = new char[cols];
	}

	for (GLint i = rows - 1; i > -1; i--)
	{
		in.ignore(10, '\n');
		for (GLint j = 0; j < cols; j++)
		{
			in >> levelField[i][j];
		}
	}
	in.close();
}
GLint LevelManager::getCols()
{
	return cols;
}
GLint LevelManager::getRows()
{
	return rows;
}
bool LevelManager::levelUp()
{
	if (levelNum < totalLevels)
	{
		levelNum++;
		return true;
	}
	return false;
}
char LevelManager::getCell(GLint row, GLint col)
{
	return levelField[row][col];
}
GLint LevelManager::getStartR()
{
	return startR;
}
GLint LevelManager::getStartC()
{
	return startC;
}
GLint LevelManager::getEndR()
{
	return endR;
}
GLint LevelManager::getEndC()
{
	return endC;
}

void LevelManager::reset()
{
	levelNum = 0;
}

void LevelManager::draw()
{
	char temp[40];
	snprintf(temp, 40, "LEVEL :  %d", levelNum);
	iG::iSetColor(RED);
	iG::iText(iG::iGetWindowWidth() - 200, iG::iGetWindowHeight() - 150, temp);
}