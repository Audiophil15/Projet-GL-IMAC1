#ifndef MENU_H
#define MENU_H

#include "window.h"
#include "rectangle.h"

int menu(Window win);
bool isIn(Rectangle choix, SDL_MouseButtonEvent click, Window win);
bool isOver(Rectangle choix, SDL_MouseMotionEvent click, Window win);


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
