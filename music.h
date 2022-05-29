#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>
#include <string>


class Music {
	private :

	Mix_Music* music;
	std::string filename;


	public:
	Music(std::string filename);

	void initializeFromFile(std::string filename);
	void play();
	void free(); 
	void pauseorplay();
	void stop();
	void replay();

};

#endif