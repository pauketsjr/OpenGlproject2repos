/*
Normal output screen is in text mode .
We need a screen which is in graphics mode to do graphical work . Opengl does that .
*/
#include "GameManager.h"

GLint iG::iWindowWidth;
GLint iG::iWindowHeight;
GLint iG::iWindowX;
GLint iG::iWindowY;
GLint iG::iScreenWidth;
GLint iG::iScreenHeight;
GLfloat iG::iClearR;
GLfloat iG::iClearG;
GLfloat iG::iClearB;

void iG::iInitialize(const char* title)
    {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
        glutInitWindowSize(iWindowWidth , iWindowHeight ) ;        // Window Size
        glutInitWindowPosition(iWindowX,iWindowY) ;     // Window Position
        glutCreateWindow(title);    // Window Title
        glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;     // Window Background Color
        glMatrixMode( GL_PROJECTION) ;
        glLoadIdentity() ;
        // default window range is (-1,1) in x and (-1,1) in y
        glOrtho(0.0 , iWindowWidth , 0.0 , iWindowHeight , -1.0 , 1.0);    // Setting window range (0,iWindowWidth) in x and (0,iWindowHeight) in y   
        iClear();

        glutDisplayFunc(displayFF);     // Window Display Callback
        glutKeyboardFunc(keyboardHandler1FF); // Callback when normal key is pressed down
        glutSpecialFunc(keyboardHandler2FF);  // Callback when special key is pressed down
      
        glEnable(GL_BLEND);     // Transparent Color
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Transparent Color
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(2.0);       // Width of drawing lines

        glutFullScreen();      // Toggle fullscreen
        glutSetCursor(GLUT_CURSOR_NONE);    // Hiding the cursor
    }
