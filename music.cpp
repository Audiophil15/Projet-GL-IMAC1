#include <string>
#include <SDL2/SDL_mixer.h>

#include "music.h"



void Music::initializeFromFile(std::string filename){
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{
		printf("%s", Mix_GetError());
	}
	Mix_FreeMusic(this->music);
	char chemin = sprintf("src/sons/%c.mp3", filename.c_str());
	this->music = Mix_LoadMUS(chemin);
}

void Music::play(){
	Mix_PlayMusic(this->music, -1); //-1 = infinitely played
}

void Music::free(){
	Mix_FreeMusic(this->music); 
	Mix_CloseAudio(); 
}


void Music::pauseorplay(){
	if(Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic(); 
	}
	else
	{
		Mix_PauseMusic(); 
	}
}

void Music::stop(){
	Mix_HaltMusic();
}

void Music::replay(){
	Mix_RewindMusic();
}