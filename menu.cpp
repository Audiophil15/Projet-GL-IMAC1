#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>

#include "window.h"
#include "graphics.h"


int menu(Window win){
	//une fonction qui affiche le menu
	//une fonction qui gère les évènements

	int quit = 0;
	SDL_Event e;

	SDL_Surface* img= IMG_Load("./src/menu.png");
	if(img==NULL){
		exit(-1);
	}

	GLuint menu;

	menu = initializeTexture(img);

	while(!quit){

		while(SDL_PollEvent(&e)){
			switch (e.type){
			case SDL_QUIT:
				quit = 1;
			break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED){
					windowResize(e.window.data1, e.window.data2, win);
				}
			break;

			case SDL_KEYDOWN :
				switch(e.key.keysym.sym){
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = 1;
					break;

					case SDLK_TAB :

						if(chara.selectedChara <2){
							chara.selectedChara+=1;
						}else {
							chara.selectedChara=0;
						}

						if(chara.selectedChara> 0){
							chara.previousChara= chara.selectedChara - 1;
						}else{
							chara.previousChara =2;
						}

						selectedBlock = charaTab[chara.selectedChara];

					break;


					case SDLK_UP:
						selectedBlock.jump();
					break;

				}	
			break;

			case SDL_MOUSEMOTION : 

			default:
			break;
			}
		}

		

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureMenu(menu, win);

		SDL_GL_SwapWindow(win.SDLWindow);
	}	
	deleteTexture(&menu, img);

}





