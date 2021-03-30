#include "Box.h"
Box::Box()
{
	this->width = 0;
	this->height = 0;
}
Box::Box(GLfloat width, GLfloat height)
{
	this->width = width;
	this->height = height;
}
void Box::setWidth(GLfloat width)
{
	this->width = width;
}
void Box::setHeight(GLfloat height)
{
	this->height = height;
}
GLfloat Box::getHeight()
{
	return this->height;
}
GLfloat Box::getWidth()
{
	return this->width;
}
void Box::draw()
{
	iG::iSetColor(getColor());
	iG::iRectangle(x,y,width,height);
}
void Box::setBounds(GLint x, GLint y, GLint width, GLint height)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}