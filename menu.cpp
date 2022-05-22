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

Choice::Choice():rectangle({0.,0.,0.,0.}){}

Choice::Choice(Rectangle rect):rectangle(rect){}

Choice::Choice(Rectangle rect, GLuint txtBack):rectangle(rect), textureBack(txtBack){}

Choice::Choice(Rectangle rect, GLuint txtBack, GLuint txtFront):rectangle(rect), textureBack(txtBack), textureFront(txtFront){}



int menu(Window win){



	//play
	SDL_Surface* playw= IMG_Load("./src/1.png");
	if(playw==NULL){
		exit(-1);
	}
	GLuint textPlayW;
	textPlayW = initializeTexure(playw);

	SDL_Surface* playb= IMG_Load("./src/1bis.png");
	if(playb==NULL){
		exit(-1);
	}
	GLuint textPlayB;
	textPlayB = initializeTexure(playb);



	//rules
	SDL_Surface* rulesw= IMG_Load("./src/2.png");
	if(rulesw==NULL){
		exit(-1);
	}
	GLuint textRulesW;
	textRulesW = initializeTexure(rulesw);

	SDL_Surface* rulesb= IMG_Load("./src/2bis.png");
	if(playb==NULL){
		exit(-1);
	}
	GLuint textRulesB;
	textRulesB = initializeTexure(rulesb);




	//options
	SDL_Surface* optionsw= IMG_Load("./src/3.png");
	if(optionsw==NULL){
		exit(-1);
	}
	GLuint textOptionsW;
	textOptionsW = initializeTexure(optionsw);

	SDL_Surface* optionsb= IMG_Load("./src/3bis.png");
	if(optionsb==NULL){
		exit(-1);
	}
	GLuint textOptionsB;
	textOptionsB = initializeTexure(optionsb);



	//quit
	SDL_Surface* quitw= IMG_Load("./src/4.png");
	if(quitw==NULL){
		exit(-1);
	}
	GLuint textQuitW;
	textQuitW = initializeTexure(quitw);

	SDL_Surface* quitb= IMG_Load("./src/4bis.png");
	if(quitb==NULL){
		exit(-1);
	}
	GLuint textQuitB;
	textQuitB = initializeTexure(quitb);
	


	// std::vector<GLuint>tabTexture;

	// SDL_Surface* choice;

	// for(int i=0; i<4; i++){
	// 	char chemin[50];
	// 	sprintf(chemin, "./src/%d", i);
	// 	choice = IMG_Load(chemin);
		
	// 	if(choice==NULL){
    //     exit(-1);
    //     }

	// 	tabTexture.push_back(initializeTexure(choice));
	// }
	

	Rectangle rectPlay(65.,33., 10., 3.);
	Rectangle rectRules(62., 28., 13., 3.);
	Rectangle rectOptions(57.,23., 18., 3.); 
	Rectangle rectQuit(65., 17., 10., 4.);


	Choice playc(rectPlay, textPlayW, textPlayB);
	Choice rulesc(rectRules, textRulesW, textRulesB);
	Choice optionsc(rectOptions, textOptionsW, textOptionsB);
	Choice quitc(rectQuit, textQuitW, textQuitB);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(playc);
	tabChoice.push_back(rulesc);
	tabChoice.push_back(optionsc);
	tabChoice.push_back(quitc);
	

	Choice selected = tabChoice[nbC];





	int quit = 0;
	SDL_Event e;

	//background
	SDL_Surface* textBackground= IMG_Load("./src/background.png");
	if(textBackground==NULL){
		exit(-1);
	}
	GLuint menu;
	menu = initializeTexure(textBackground);


	


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


					case SDLK_UP:
						if(nbC>0){
							nbC-=1;
							printf("nbC vaut :%d \n", nbC);
							
						}else{
							nbC=3;
							printf("nbC vaut :%d \n", nbC);
						}

						selected = tabChoice[nbC];
					

					break;

					case SDLK_DOWN:
					if(nbC<3){
						nbC+=1;
						printf("nbC vaut :%d \n", nbC);
					}else{
						nbC=0;
						printf("nbC vaut :%d \n", nbC);
					}
					selected = tabChoice[nbC];
					break;

					case SDLK_RETURN:
					printf("enter push");

					quit = 1;
					printf("\n");
					break;

				}	
			break;

			case SDL_MOUSEBUTTONDOWN:

				if(isIn(playc.rectangle, e.button, win)){
					nbC=0;
					

					quit = 1;

					printf("nbC vaut :%d \n", nbC);
					printf("click is in play");

					printf("\n");
				}
				else if(isIn(rulesc.rectangle, e.button, win)){
					nbC=1;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in rules");
					printf("\n");
				}
				else if(isIn(optionsc.rectangle, e.button, win)){
					nbC=2;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in options");
					printf("\n");
				}
				else if(isIn(quitc.rectangle, e.button, win)){
					nbC=3;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in quit");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
			

			if(isOver(playc.rectangle, e.motion, win)){
					selected = tabChoice[0];
			}
			else if(isOver(rulesc.rectangle, e.motion, win)){
				selected = tabChoice[1];
			}
			else if(isOver(optionsc.rectangle, e.motion, win)){
				selected = tabChoice[2];
			}
			else if(isOver(quitc.rectangle, e.motion, win)){
				selected = tabChoice[3];
			} else {
				
			}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureBackground(menu, win);

		textureMenu(playc);
		textureMenu(rulesc);
		textureMenu(optionsc);
		textureMenu(quitc);

		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	


	deleteTexture(&menu, textBackground);

	deleteTexture(&textPlayW, playw);
	deleteTexture(&textPlayB, playb);


	deleteTexture(&textRulesW, rulesw);
	deleteTexture(&textRulesB, rulesb);

	deleteTexture(&textOptionsW, optionsw);
	deleteTexture(&textOptionsB, optionsb);

	deleteTexture(&textQuitW, quitw);
	deleteTexture(&textQuitB, quitb);


	return nbC;

}



bool isOver(Rectangle choix, SDL_MouseMotionEvent over, Window win){
	return(choix.getPosX()<=mapWindowToGLcoordinateX(over.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(over.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(over.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(over.y, win));
}

bool isIn(Rectangle choix, SDL_MouseButtonEvent click, Window win){
	
	return(choix.getPosX()<=mapWindowToGLcoordinateX(click.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(click.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(click.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(click.y, win));
}


 





