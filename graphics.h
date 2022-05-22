#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_image.h>
#include <string>



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

GLuint initializeTexure(std::string chemin);

void textureBackground(GLuint texture, Window win);

void textureMenu(Choice texture);

void textureMenuTop(Choice texture);


void deleteTexture(GLuint *texture);

#endif

