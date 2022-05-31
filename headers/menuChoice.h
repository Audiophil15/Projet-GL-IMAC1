#ifndef MENUCHOICE_H
#define MENUCHOICE_H

#include <GL/gl.h>
#include "rectangle.h"

class Choice{

	public :
	Rectangle rectangle;
	GLuint textureBack;
	GLuint textureFront;


	Choice();
	Choice(Rectangle rect);
	Choice(Rectangle rect, GLuint txtBack);
	Choice(Rectangle rect, GLuint txtBack, GLuint txtFront);

};

#endif