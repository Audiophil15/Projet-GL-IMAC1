#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <string>

#include "menu.h"
#include "menuChoice.h"
#include "window.h"

void initSDL();
SDL_Window* initWindow(int width, int height);
SDL_GLContext contextInit(SDL_Window* window);

void windowResize(int newWidth, int newHeight, Window& win);
void onWindowResized(Window w);

int coordinatesXConvert(int windowCoord);
int mapWindowToGLcoordinateX(int windowCoord, Window w);
int mapWindowToGLcoordinateY(int windowCoord, Window w);

GLuint initializeTexure(std::string chemin);
void textureBackground(GLuint texture, Window win);
void textureMenu(Choice texture);
void textureMenuTop(Choice texture);
void deleteTexture(GLuint *texture);

void axis(int baseW, int baseH);


#endif

