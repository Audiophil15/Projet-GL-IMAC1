// #include <string>
// #include <SDL2/SDL_mixer.h>

// #include "music.h"

// // Music::Music(std::string filename):filename(filename){};

// void Music::initializeFromFile(std::string filename){
// 	FILE* file = fopen(filename.c_str() , "r");
// 	char* levelMusic;
// 	char parameter[10];
// 	char line[50];
// 	char copy[50];


// 	do{
// 		fscanf(file, "%[^\n] ", line);
// 		strcpy(copy, line);
// 		strcpy(parameter, strtok(copy, " "));
// 		// printf("%s\n", line);

// 		switch(parameter[0]){
// 			case 'm' :{ 
// 				sscanf(line, "%*s %s", levelMusic);
// 			}
// 			break;

// 			default:
// 			break;

// 		}

// 	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));

// 	fclose(file);
	

// 	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
// 	{
// 		printf("%s", Mix_GetError());
// 	}
// 	Mix_FreeMusic(this->music);
// 	// char* chemin;
// 	// sprintf(chemin, "src/sons/%s.mp3", filename.c_str());
// 	this->music = Mix_LoadMUS(levelMusic);
// }

// void Music::play(){
// 	Mix_PlayMusic(this->music, -1); //-1 = infinitely played
// }

// void Music::free(){
// 	Mix_FreeMusic(this->music); 
// 	Mix_CloseAudio(); 
// }


// void Music::pauseorplay(){
// 	if(Mix_PausedMusic() == 1)
// 	{
// 		Mix_ResumeMusic(); 
// 	}
// 	else
// 	{
// 		Mix_PauseMusic(); 
// 	}
// }

// void Music::stop(){
// 	Mix_HaltMusic();
// }

// void Music::replay(){
// 	Mix_RewindMusic();
// }