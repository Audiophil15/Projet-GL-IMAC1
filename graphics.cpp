#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "graphics.h"
#include "window.h"

void initSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error initializing : %s\n", SDL_GetError());
		exit(11);
	}
}

SDL_Window* initWindow(int width, int height){
	SDL_Window* w;

	w = SDL_CreateWindow("Rectangle and Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (w==NULL){
		printf("Error creating window : %s\n", SDL_GetError());
		exit(12);
	}
	return w;
}

SDL_GLContext contextInit(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if(context == NULL){
		printf("Error creating OpenGL context : %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(16);
	}

	return context;

}

int mapWindowToGLcoordinateX(int windowCoord, Window w){
	int shift;
	float ratio;
	if (w.scrW/w.scrH > w.ratio){
		shift = (w.scrW-w.scrH*w.ratio)/2;
		ratio = w.baseH/w.scrH;
	} else {
		shift = 0;
		ratio = w.baseW/w.scrW;
	}

	return (windowCoord - shift)*ratio;
}

int mapWindowToGLcoordinateY(int windowCoord, Window w){
	int shift;
	float ratio;
	if (w.scrW/w.scrH < w.ratio){
		shift = (w.scrH-w.scrW/w.ratio)/2;
		ratio = w.baseW/w.scrW;
	} else {
		shift = 0;
		ratio = w.baseH/w.scrH;
	}

	return (w.scrH - windowCoord - shift)*ratio;
}

void windowResize(int newWidth, int newHeight, Window& win){
	win.scrW = (float)newWidth;
	win.scrH = (float)newHeight;
	onWindowResized(win);
}

void onWindowResized(Window w){
	// printf("Window resized : %4d, %-4d\n", w.scrW, w.scrH);
	// If screen is wider than original window
	if(w.scrW/(float)w.scrH > w.ratio){
		glViewport(0+(w.scrW-w.scrH*w.ratio)/2, 0, w.scrH*w.ratio, w.scrH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	} else {
		glViewport(0,0+(w.scrH-w.scrW/w.ratio)/2, w.scrW, w.scrW/w.ratio);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}
	gluOrtho2D(
	0, w.baseW,
	0, w.baseH);
}