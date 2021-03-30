#ifndef __I_GRAPHICS__
#define __I_GRAPHICS__
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <fstream>
#define PI (acos(-1.0))
using namespace std;
class iG {
protected:
	static GLint iWindowHeight, iWindowWidth, iScreenHeight, iScreenWidth, iWindowX, iWindowY;
	static GLfloat iClearR, iClearG, iClearB;
public:
	static void iDraw();
	static void iKeyboard(unsigned char);
	static void iSpecialKeyboard(unsigned char);

	// Callback functions
	static void displayFF(void)		// Display Callback
	{
		iDraw();
		glutSwapBuffers();
	}
	static void keyboardHandler1FF(unsigned char key, GLint x, GLint y)	  // Callback When normal key is pressed down
	{
		iKeyboard(key);
		glutPostRedisplay();
	}
	static void keyboardHandler2FF(GLint key, GLint x, GLint y)	// Callback when special key is pressed down
	{
		iSpecialKeyboard(key);
		glutPostRedisplay();
	}

	static void iClear()	// Clears the screen
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(iClearR / 255, iClearG / 255, iClearB / 255, 1.0);
		glFlush();
	}

	static GLint iGetWindowHeight()
	{
		return iWindowHeight;
	}
	static GLint iGetWindowWidth()
	{
		return iWindowWidth;
	}
	static void iSetWindowHeight(GLint height)
	{
		iWindowHeight = height;
	}
	static void iSetWindowWidth(GLint width)
	{
		iWindowWidth = width;
	}
	static GLint iGetScreenHeight()
	{
		return iScreenHeight;
	}
	static GLint iGetScreenWidth()
	{
		return iScreenWidth;
	}
	static void iSetScreenHeight(GLint height)
	{
		iScreenHeight = height;
	}
	static void iSetScreenWidth(GLint width)
	{
		iScreenWidth = width;
	}
	static void iSetWindowX(GLfloat x)
	{
		iWindowX = x;
	}
	static void iSetWindowY(GLfloat y)
	{
		iWindowY = y;
	}

	// Draw texts
	static void iText(GLfloat x, GLfloat y, const char* str, void* font = GLUT_BITMAP_TIMES_ROMAN_24)	//GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
	{
		glRasterPos3d(x, y, 0);
		GLint i;
		for (i = 0; str[i]; i++) {
			glutBitmapCharacter(font, str[i]);
		}
	}

	// Draw Big texts
	static void iBigText(GLfloat x, GLfloat y, const char* str, void* font = GLUT_STROKE_ROMAN)
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		GLint i;
		for (i = 0; str[i]; i++)
			glutStrokeCharacter(font, str[i]); // GLUT_STROKE_ROMAN  , GLUT_STROKE_MONO_ROMAN
		glPopMatrix();
	}
	// Overloaded
	static void iBigText(GLfloat x, GLfloat y, string str, void* font = GLUT_STROKE_ROMAN)
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		GLint i;
		for (i = 0; str[i]; i++)
			glutStrokeCharacter(font, str[i]); // GLUT_STROKE_ROMAN  , GLUT_STROKE_MONO_ROMAN
		glPopMatrix();
	}

	// Sets color for drawing
	static void iSetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0)
	{
		// r,g,b should be 0 to 1
		r /= 255.0;
		g /= 255.0;
		b /= 255.0;
		glColor4f(r, g, b, a);
	}
	// Overloaded
	static void iSetColor(tuple<GLfloat, GLfloat, GLfloat> rgb, GLfloat a = 1.0)
	{
		GLfloat r = get<0>(rgb), g = get<1>(rgb), b = get<2>(rgb);
		// r,g,b should be 0 to 1
		r /= 255.0;
		g /= 255.0;
		b /= 255.0;
		glColor4f(r, g, b, a);
	}

	// Sets Background color
	static void iSetBGColor(GLfloat r, GLfloat g, GLfloat b)
	{
		iClearR = r;
		iClearG = g;
		iClearB = b;
	}

	// Draw Circle
	static void iCircle(GLfloat x, GLfloat y, GLfloat r, GLint slices = 100)
	{
		// Draw circle filler
		GLfloat t, dt = 2 * PI / slices;
		glBegin(GL_POLYGON);
		for (t = 0; t <= 2 * PI + dt; t += dt)
		{
			glVertex2f(x + r * cos(t), y + r * sin(t));
		}
		glEnd();

		// Draw Circle border
		glColor4f(0, 0, 0, 1);
		glBegin(GL_LINE_STRIP);
		for (t = 0; t <= 2 * PI + dt; t += dt)
		{
			glVertex2f(x + r * cos(t), y + r * sin(t));
		}
		glEnd();
	}

	// Draws a rectangle
	static void iRectangle(GLfloat left, GLfloat bottom, GLfloat width, GLfloat height)
	{
		GLfloat x1, y1, x2, y2;
		x1 = left;
		y1 = bottom;
		x2 = x1 + width;
		y2 = y1 + height;

		// Draw rectangle filler
		glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glVertex2f(x1, y1);
		glEnd();

		// Draw rectangle border
		glColor4f(0, 0, 0, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glVertex2f(x1, y1);
		glEnd();
	}

	static void iShowImage(GLfloat x, GLfloat y,GLfloat width,GLfloat height, unsigned char* image);
	// Opengl window setup 
	static void windowSetup();

	// Initializing opengl Program
	static void iInitialize(const char* title);
};
#endif









