#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include "graphics.h"
#include "gameEnvironment.h"
#include "window.h"

int main(){

	Window win;

	initSDL();

	GameEnvironment gameEnvironment;
	gameEnvironment.window.SDLWindow = initWindow(gameEnvironment.window.scrW, gameEnvironment.window.scrH);
	gameEnvironment.window.GLContext = contextInit(gameEnvironment.window.SDLWindow);

	windowResize(gameEnvironment.window.scrW, gameEnvironment.window.scrH, gameEnvironment.window);

	gameEnvironment.startGame();

	SDL_GL_DeleteContext(gameEnvironment.window.GLContext);
	SDL_DestroyWindow(gameEnvironment.window.SDLWindow);
	SDL_Quit();

}
