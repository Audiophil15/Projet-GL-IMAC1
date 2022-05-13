#ifndef MENU_H
#define MENU_H

#include "window.h"
#include "rectangle.h"

int menu(Window win);
bool isIn(Rectangle choix, SDL_MouseButtonEvent click, Window win);


class Choice{

	public :
	Rectangle rectangle; 
	GLuint textureBack;
	GLuint textureFront;

	bool selectedChoice = 0;
	int numberChoice;

	Choice();
	Choice(int nbChoice);
	Choice(int nbChoice, bool slChoice);
	Choice(int nbChoice, bool slChoice, Rectangle rect);
	Choice(int nbChoice, bool slChoice, Rectangle rect, GLuint txtBack, GLuint txtFront);

};

#endif
