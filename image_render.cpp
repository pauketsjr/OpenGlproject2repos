#include "GameManager.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Opengl\\include\\stb_image.h"
#endif

void iG::iShowImage(GLfloat x, GLfloat y, GLfloat width, GLfloat height,unsigned char* image)
{
	// int  width, height, n;
	// stbi_set_flip_vertically_on_load(true);	 // Without this image will show upside down
	// unsigned char* image = stbi_load(filename, &width, &height, &n, 4);		// Allocating memory for image
	glRasterPos3f(x, y,0);	// Setting image position
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);	// Showing image
	// stbi_image_free(image);	  // Deallocating memory
}	