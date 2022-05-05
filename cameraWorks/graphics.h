#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "window.h"

void initSDL();
SDL_Window* initWindow(int width, int height);
SDL_GLContext contextInit(SDL_Window* window);
int coordinatesXConvert(int windowCoord);
int mapWindowToGLcoordinateX(int windowCoord, Window w);
int mapWindowToGLcoordinateY(int windowCoord, Window w);
void windowResize(int newWidth, int newHeight, Window& win);
void onWindowResized(Window w);

#endif

