#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
	public :
		const float baseH;
		const float baseW;
		const float ratio;
		float scrH, scrW;
		SDL_Window* SDLWindow;
		SDL_GLContext GLContext;

		Window();
		Window(int width, int height);
		Window(int glwidth, int glheight, int width, int height);
};

#endif