#ifndef MENU_H
#define MENU_H

#include <string>

#include "window.h"
#include "rectangle.h"

int menu(Window win, std::string background, std::vector<std::string> choices, std::vector<Rectangle> boxes, int l);
// int menu(Window win);
int choiceLevel(Window win);
int menuPause(Window win);
int menuRules(Window win);
int menuSettings(Window win);
int menuVictory(Window win);
int menuGameOver(Window win);
int menuFinal(Window win);
int mainMenu(Window win);


bool clickIn(Rectangle choix, SDL_MouseButtonEvent click, Window win);
bool hover(Rectangle choix, SDL_MouseMotionEvent click, Window win);




#endif
