#ifndef __TILES_MANAGER__
#define __TILES_MANAGER__
#include "GameManager.h"
#include "Tile.h"
#include "Box.h"
class TilesManager
{
	Tile** tilesField;
	GLint width, height;	// Of a single tile
	GLint rows, cols;		// Total in a level
	GLint visibleRows, visibleCols;	// Visible in screen
	unsigned char* image;
	int imageWidth, imageHeight;
	
public:
	GLfloat offsetRows, offsetCols;
	GLfloat tileOffsetX, tileOffsetY;
	TilesManager();
	~TilesManager();
	void init();
	void set();
	char getCell(GLint, GLint);
	void setCell(GLint, GLint, char);
	GLint getRows();
	GLint getCols();
	GLint getWidth();
	GLint getHeight();
	void draw();
};
#endif
