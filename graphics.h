#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "window.h"
#include "menu.h"

void initSDL();
SDL_Window* initWindow(int width, int height);
SDL_GLContext contextInit(SDL_Window* window);
int coordinatesXConvert(int windowCoord);
int mapWindowToGLcoordinateX(int windowCoord, Window w);
int mapWindowToGLcoordinateY(int windowCoord, Window w);
void windowResize(int newWidth, int newHeight, Window& win);
void onWindowResized(Window w);

GLuint initializeTexure(SDL_Surface* img);
void textureBackground(GLuint texture, Window win);

void textureMenu(Choice texture);

void textureMenuTop(Choice texture);


void deleteTexture(GLuint *texture, SDL_Surface* img);

#endif

