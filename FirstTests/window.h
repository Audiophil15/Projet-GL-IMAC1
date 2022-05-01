#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
	public :
		const float baseH = 400;
		const float baseW = 800;
		const float ratio = 2.0;
		float scrH, scrW;
		SDL_Window* SDLWindow;
		SDL_GLContext GLContext;

		Window();
};

#endif