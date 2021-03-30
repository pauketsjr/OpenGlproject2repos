#include "ScoreManager.h"
#include "Color.h"
#include "MenuManager.h"

extern MenuManager menu;
extern GameManager game;
ScoreManager::ScoreManager()
{
	currentScore = 0;
	selectedR = 0;
	totalR = 0;
}
void ScoreManager::reset()
{
	currentScore = 0;
}
void ScoreManager::increase()
{
	currentScore += 10;
}
void ScoreManager::draw()
{
	iG::iSetColor(YELLOW,0.7);
	iG::iRectangle(iG::iGetWindowWidth() - 250.0f, iG::iGetWindowHeight() - 240.0f, 250.0f, 240.0f);

	char temp[40];
	snprintf(temp, 40, "SCORE :  %d", currentScore);
	iG::iSetColor(RED);
	iG::iText(iG::iGetWindowWidth() - 200.0f, iG::iGetWindowHeight() - 50.0f, temp);	
}
void ScoreManager::drawGameOver()
{
	char temp[40];

	// Draw Score
	snprintf(temp, 40, "SCORE : %d", currentScore);
	iG::iSetColor(BLACK);
	iG::iBigText(iG::iGetWindowWidth() / 2.0f - 530, iG::iGetWindowHeight() - 300.0f, temp);

	// Draw name entry
	glPushMatrix();
	glTranslatef(iG::iGetWindowWidth() / 2.0f - 630, iG::iGetWindowHeight() / 2.0f - 30, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);
	iG::iSetColor(BLACK);
	iG::iBigText(0, 0, name);
	glPopMatrix();
}

void ScoreManager::drawBoard()
{
	GLint i;
	// Draw Header
	glPushMatrix();
	glTranslatef(iG::iGetWindowWidth() / 2.0f, iG::iGetWindowHeight(), 0.0f);
	glScalef(0.6f, 0.6f, 1.0f);
	iG::iSetColor(RED);
	iG::iBigText(-1000, -200, "NAME");
	iG::iBigText(-200, -200, "TIME");
	iG::iBigText(600, -200, "SCORE");
	glPopMatrix();

	// Draw scores
	ifstream in;
	in.open("Data\\HIGHSCORE.txt", ios::in);
	for (i = 0;!in.eof();i++)
	{
		string str, s,t;
		in >> str >> t >> s;

		if (selectedR == i)
		{
			iG::iSetColor(YELLOW);
			iG::iRectangle(iG::iGetWindowWidth() / 2.0f - 800, iG::iGetWindowHeight() - 225.0f - i * 83, 1600.0f, 70.0f);
		}

		glPushMatrix();
		glTranslatef(iG::iGetWindowWidth() / 2.0f, iG::iGetWindowHeight(), 0.0f);
		glScalef(0.45f, 0.45f, 1.0f);
		iG::iSetColor(BLACK);
		iG::iBigText(-1100.0f - str.length() * 35.0, -470.0f - i * 185, str);
		iG::iBigText(-250.0f, -470.0f - i * 185, t);
		iG::iBigText(800.0f, -470.0f - i * 185, s);
		glPopMatrix();
	}
	in.close();

	// Draw instructions
	iG::iSetColor(RED);
	iG::iText(iG::iGetWindowWidth() / 2.0f - 150, 20.0f, "Press e to edit and d to delete");
	totalR = i;
}

struct ScoreType
{
	string name;
	GLint time;
	GLint score;
};
void read(vector<ScoreType>& scoreSheet)
{
	ifstream in;
	in.open("Data\\Highscore.txt", ios::in);
	while (!in.eof())
	{
		string str;
		GLint s;
		GLint t;
		in >> str >> t >> s;
		if (str != "")
		{
			scoreSheet.push_back({ str, t , s });
		}
	}
	in.close();
}
void write(vector<ScoreType>& scoreSheet)
{
	GLint i;
	ofstream out;
	out.open("Data\\Highscore.txt", ios::out);
	for (i = 0; i < scoreSheet.size() - 1 && i < 9; i++)
	{
		out << scoreSheet[i].name << " " << scoreSheet[i].time<<" "<<scoreSheet[i].score << endl;
	}
	out << scoreSheet[i].name << " " << scoreSheet[i].time << " " << scoreSheet[i].score;
	out.close();
}
void ScoreManager::save()
{
	vector<ScoreType> scoreSheet;
	read(scoreSheet);
	ScoreType temp = { name, game.getTime() , currentScore };
	GLint i;
	for (i = 0; i < scoreSheet.size(); i++)
	{
		if (currentScore > scoreSheet[i].score)
		{
			scoreSheet.insert(scoreSheet.begin() + i, temp);
			break;
		}
		else if (currentScore == scoreSheet[i].score && game.getTime() < scoreSheet[i].time)
		{
			scoreSheet.insert(scoreSheet.begin() + i, temp);
			break;
		}
	}
	if (i == scoreSheet.size() && i < 10)
	{
		scoreSheet.push_back(temp);
	}
	write(scoreSheet);
	totalR = scoreSheet.size();
}


void ScoreManager::erase()
{
	vector<ScoreType> scoreSheet;
	read(scoreSheet);
	scoreSheet.erase(scoreSheet.begin() + selectedR);
	write(scoreSheet);
	totalR = scoreSheet.size();
}

void ScoreManager::edit()
{
	vector<ScoreType> scoreSheet;
	read(scoreSheet);
	currentScore = scoreSheet[selectedR].score;
	scoreSheet.erase(scoreSheet.begin() + selectedR);
	write(scoreSheet);
	totalR = scoreSheet.size();
	menu.set(MenuManager::GAMEOVER);
}

void ScoreManager::nameEntry(unsigned char key)
{
	switch (key)
	{
	case '\r':
		if (!name.empty())
		{
			save();
			name.clear();
			menu.set(MenuManager::MAIN);
		}
		break;
	case '\b':
		if (!name.empty())
		{
			name.pop_back();
		}
	case ' ':
		break;
	default:
		if (name.length() < 25)
		{
			name += key;
		}
		break;
	}
}

void ScoreManager::keyUp()
{
	if (selectedR > 0)
	{
		selectedR--;
	}
	else
	{
		selectedR = totalR - 1;
	}
}
void ScoreManager::keyDown()
{
	if (selectedR < totalR - 1)
	{
		selectedR++;
	}
	else
	{
		selectedR = 0;
	}
}