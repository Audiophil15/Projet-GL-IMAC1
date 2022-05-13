#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>


#include "window.h"
#include "graphics.h"
#include "rectangle.h"
#include "menu.h"

Choice::Choice():numberChoice(0){}

Choice::Choice(int nbChoice):numberChoice(nbChoice){}

Choice::Choice(int nbChoice, bool slChoice):numberChoice(nbChoice), selectedChoice(slChoice){}

Choice::Choice(int nbChoice, bool slChoice, Rectangle rect):numberChoice(nbChoice), selectedChoice(slChoice), rectangle(rect){}

Choice::Choice(int nbChoice, bool slChoice, Rectangle rect, GLuint txtBack, GLuint txtFront):numberChoice(nbChoice), selectedChoice(slChoice), rectangle(rect), textureBack(txtBack), textureFront(txtFront){}



int menu(Window win){
	//une fonction qui affiche le menu
	//une fonction qui gère les évènements
	

	Rectangle textPlay(65.,32., 11., 3.);
	Rectangle textRules(62., 27., 14., 4.);
	Rectangle textOptions(57.,22., 19., 4.); 
	Rectangle textQuit(65.,18., 11., 4.);


	Choice playc(0, true, textPlay);
	Choice rulesc(1, false, textRules);
	Choice optionsc(2, false, textOptions);
	Choice quitc(3, false, textQuit);


	



	

	// std::vector<Choice> choices;
	// choices.push_back(textPlay);
	// choices.push_back(textRules);
	// choices.push_back(textOptions);
	// choices.push_back(textQuit);

	// printf("la taille est : %ld \n", choices.size());

	//avoir deux textures textes placées au meme endroit
	


	

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

					// case SDLK_TAB :

					// 	if(chara.selectedChara <2){
					// 		chara.selectedChara+=1;
					// 	}else {
					// 		chara.selectedChara=0;
					// 	}

					// 	if(chara.selectedChara> 0){
					// 		chara.previousChara= chara.selectedChara - 1;
					// 	}else{
					// 		chara.previousChara =2;
					// 	}

					// 	selectedBlock = charaTab[chara.selectedChara];

					// break;


					case SDLK_UP:
						// selectedBlock.jump();
						printf("test fleche haut ok \n");

					break;

					case SDLK_DOWN:
						printf("test fleche bas ok \n");
					break;

				}	
			break;

			case SDL_MOUSEBUTTONDOWN:

				if(isIn(playc.rectangle, e.button, win)){
					printf("click is in play");
					printf("\n");
				}
				else if(isIn(rulesc.rectangle, e.button, win)){
					printf("clicks is in rules");
					printf("\n");
				}
				else if(isIn(optionsc.rectangle, e.button, win)){
					printf("clicks is in options");
					printf("\n");
				}
				else if(isIn(quitc.rectangle, e.button, win)){
					printf("clicks is in quit");
					printf("\n");
				} else {
					printf("error");
					printf("\n");
				}
			break;

			case SDL_MOUSEMOTION :
			printf("pos x: %d \n", mapWindowToGLcoordinateX(e.motion.x, win));
			printf("pos y: %d \n", mapWindowToGLcoordinateY(e.motion.y, win));
			printf("\n");




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

	return 0;

}


// int collision(block b1, block b2){
// 	// Symetric relation
// 	if (b1.hitbox.x+b1.hitbox.w < b2.hitbox.x || b2.hitbox.x+b2.hitbox.w < b1.hitbox.x || b2.hitbox.y > b1.hitbox.y+b1.hitbox.h || b2.hitbox.y+b2.hitbox.h < b1.hitbox.y){
// 		return 0;
// 	}
// 	return 1;
// }

bool isIn(Rectangle choix, SDL_MouseButtonEvent click, Window win){
	
	if(choix.getPosX()<=mapWindowToGLcoordinateX(click.x, win) && choix.getCenterY()<=mapWindowToGLcoordinateY(click.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(click.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(click.y, win)){
		return true;
	} else {
		return false;
	}




}

 





