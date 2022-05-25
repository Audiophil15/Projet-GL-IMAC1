#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_mixer.h>
#include <string>



class Music {
	private :

	Mix_Music* music;


	public:
	void initializeFromFile(std::string filename);
	void play();
	void free(); 
	void pauseorplay();
	void stop();
	void replay();

};

#endif