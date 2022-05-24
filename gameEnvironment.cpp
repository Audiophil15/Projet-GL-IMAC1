#include <SDL2/SDL.h>

#include "gameEnvironment.h"

#include "graphics.h"
#include "window.h"
#include "menu.h"

#define LAST_LEVEL 4

GameEnvironment::GameEnvironment():quit(0){}


void GameEnvironment::startGame(){
	//
	while (!this->quit){
		switch (mainMenu(this->window)){
			case 0 :
				int level;
				level = choiceLevel(this->window);
				if (level >= 0){
					this->loadLevel(level);
					this->play(level);
					
					if (!this->quit && level == LAST_LEVEL){
						this->quit = menuFinal(this->window);
					}
				}
			break;

			case 1 :
				menuRules(this->window);
			break;

			case 2 :
				menuSettings(this->window);
			break;

			case 3 :
				this->quit = 1;
			break;
		}
	}
}

void GameEnvironment::play(int level){
	this->gameloop = 1;

	while (this->gameloop && !this->quit){
		// this->level.getCurrentPlayer()->printInputs(); //debug

		this->manageEvents();

		this->level.updateLocalEnv();
		this->level.updatePlayer();

		char path[50];
		sprintf(path, "levels/level%d\0", level+1);
		this->level.display(this->window, path);

	}
}

void GameEnvironment::manageEvents(){
	SDL_Event e;
	double levelZoom;

	while(SDL_PollEvent(&e)){
		switch (e.type){
		case SDL_QUIT:
			this->quit = 1;
		break;

		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED){
				windowResize(e.window.data1, e.window.data2, this->window);
			}
		break;
		case SDL_KEYDOWN :
			switch(e.key.keysym.sym){
				case SDLK_q:
					this->quit = 1;
				break;

				case SDLK_ESCAPE :
					levelZoom = this->window.zoom;
					this->window.zoom = 1;
					windowResize(this->window.scrW, this->window.scrH, this->window);
					printf("menu zoom : %lf", this->window.zoom);
					int choice;
					do {
						choice = mainMenu(this->window);

						switch (choice){
							case 0 :
							this->window.zoom = levelZoom;
							windowResize(this->window.scrW, this->window.scrH, this->window);
							break;

							case 1 :
								menuRules(this->window);
							break;

							case 2 :
								menuSettings(this->window);
							break;

							case 3 :
								this->quit = 1;
							break;

							case 4 :
								this->gameloop = 0;
							break;

							default:
							break;
						}
					} while(choice == 1 || choice == 2);
				break;

				case SDLK_TAB :
				this->level.switchCharacter();
				break;
			}
		break;

		default:
			//this->level.manageEvent(e);
		break;
		}
	}
}

void GameEnvironment::loadLevel(int level){
	char path[50];
	sprintf(path, "levels/level%d\0", level+1);
	this->level = Level(path);
	this->window.zoom = this->level.getZoom(path);
	windowResize(this->window.scrW, this->window.scrH, this->window);
	printf("zoom : %lf", this->window.zoom);
}
