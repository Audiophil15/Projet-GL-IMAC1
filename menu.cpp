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

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<5; i++){
	char chemin[50];
	sprintf(chemin, "./src/accueil/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureB;

	for(int i=1; i<5; i++){
	char chemin[50];
	sprintf(chemin, "./src/accueil/%dbis.png", i);

	tabTextureB.push_back(initializeTexure(chemin));
	}
	

	Rectangle rectPlay(65.,33., 10., 3.);
	Rectangle rectRules(62., 28., 13., 3.);
	Rectangle rectOptions(57.,23., 18., 3.); 
	Rectangle rectQuit(65., 17., 10., 4.);


	Choice playc(rectPlay, tabTextureW[0], tabTextureB[0]);
	Choice rulesc(rectRules, tabTextureW[1], tabTextureB[1]);
	Choice optionsc(rectOptions, tabTextureW[2], tabTextureB[2]);
	Choice quitc(rectQuit, tabTextureW[3], tabTextureB[3]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(playc);
	tabChoice.push_back(rulesc);
	tabChoice.push_back(optionsc);
	tabChoice.push_back(quitc);
	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/accueil/background.png");


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
			printf("x vaut : %d\ny vaut: %d\n\n", e.motion.x, e.motion.y);
			

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


	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureB[0]);


	deleteTexture(&tabTextureW[1]);
	deleteTexture(&tabTextureB[1]);

	deleteTexture(&tabTextureW[2]);
	deleteTexture(&tabTextureB[2]);

	deleteTexture(&tabTextureW[3]);
	deleteTexture(&tabTextureB[3]);

	printf("nbc final faut %d\n", nbC);

	return nbC;

}

int choiceLevel(Window win){

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<5; i++){
	char chemin[50];
	sprintf(chemin, "./src/levelchoice/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureC;

	for(int i=1; i<5; i++){
	char chemin[50];
	sprintf(chemin, "./src/levelchoice/%dbis.png", i);

	tabTextureC.push_back(initializeTexure(chemin));
	}
	

	Rectangle rectParis(4.,17., 21., 11.);
	Rectangle rectRome(29., 17., 21., 11.);
	Rectangle rectTokyo(54.,17., 21., 11.); 
	Rectangle rectBack(65., 2., 12., 3.);


	Choice paris(rectParis, tabTextureW[0], tabTextureC[0]);
	Choice rome(rectRome, tabTextureW[1], tabTextureC[1]);
	Choice tokyo(rectTokyo, tabTextureW[2], tabTextureC[2]);
	Choice back(rectBack, tabTextureW[3], tabTextureC[3]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(paris);
	tabChoice.push_back(rome);
	tabChoice.push_back(tokyo);
	tabChoice.push_back(back);

	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/levelchoice/background.png");


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

					case SDLK_LEFT:
					if(nbC>0){
						nbC-=1;
						printf("nbC vaut :%d \n", nbC);
						
					}else{
						nbC=3;
						printf("nbC vaut :%d \n", nbC);
					}
					selected = tabChoice[nbC];


					break;

					case SDLK_RIGHT:
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

				if(isIn(paris.rectangle, e.button, win)){
					nbC=0;
					

					quit = 1;

					printf("nbC vaut :%d \n", nbC);
					printf("click is in paris");

					printf("\n");
				}
				else if(isIn(rome.rectangle, e.button, win)){
					nbC=1;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in rome");
					printf("\n");
				}
				else if(isIn(tokyo.rectangle, e.button, win)){
					nbC=2;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in tokyo");
					printf("\n");
				}
				else if(isIn(back.rectangle, e.button, win)){
					nbC=3;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in back");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
		
			// printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(paris.rectangle, e.motion, win)){
				selected = tabChoice[0];
			}
			else if(isOver(rome.rectangle, e.motion, win)){
				selected = tabChoice[1];
			}
			else if(isOver(tokyo.rectangle, e.motion, win)){
				selected = tabChoice[2];
			}
			else if(isOver(back.rectangle, e.motion, win)){
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

		textureMenu(paris);
		textureMenu(rome);
		textureMenu(tokyo);
		textureMenu(back);

		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	


	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureC[0]);


	deleteTexture(&tabTextureW[1]);
	deleteTexture(&tabTextureC[1]);

	deleteTexture(&tabTextureW[2]);
	deleteTexture(&tabTextureC[2]);

	deleteTexture(&tabTextureW[3]);
	deleteTexture(&tabTextureC[3]);

	printf("nbc final level faut %d\n", nbC);

	return nbC;

}

int menuPause(Window win){

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<6; i++){
	char chemin[50];
	sprintf(chemin, "./src/pause/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureB;

	for(int i=1; i<6; i++){
	char chemin[50];
	sprintf(chemin, "./src/pause/%dbis.png", i);

	tabTextureB.push_back(initializeTexure(chemin));
	}
	

	Rectangle rectBackToGame(45.,33., 30., 3.);
	Rectangle rectRules(62., 28., 13., 3.);
	Rectangle rectOptions(57.,23., 18., 3.); 
	Rectangle rectQuit(65., 17., 10., 4.);
	Rectangle rectBack(65., 2., 12., 3.);




	Choice btgc(rectBackToGame, tabTextureW[0], tabTextureB[0]);
	Choice rulesc(rectRules, tabTextureW[1], tabTextureB[1]);
	Choice optionsc(rectOptions, tabTextureW[2], tabTextureB[2]);
	Choice quitc(rectQuit, tabTextureW[3], tabTextureB[3]);
	Choice back(rectBack, tabTextureW[4], tabTextureB[4]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(btgc);
	tabChoice.push_back(rulesc);
	tabChoice.push_back(optionsc);
	tabChoice.push_back(quitc);
	tabChoice.push_back(back);

	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/pause/background.png");
	// menu = initializeTexure("./src/pausefond.png");


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
							nbC=4;
							printf("nbC vaut :%d \n", nbC);
						}

						selected = tabChoice[nbC];
					

					break;

					case SDLK_DOWN:
					if(nbC<4){
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

				if(isIn(btgc.rectangle, e.button, win)){
					nbC=0;
					

					quit = 1;

					printf("nbC vaut :%d \n", nbC);
					printf("click is in back to play");

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
				}else if(isIn(back.rectangle, e.button, win)){
					nbC=4;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in back");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(btgc.rectangle, e.motion, win)){
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
			} 
			else if(isOver(back.rectangle, e.motion, win)){
				selected = tabChoice[4];	
			}else {
				
			}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureBackground(menu, win);

		textureMenu(btgc);
		textureMenu(rulesc);
		textureMenu(optionsc);
		textureMenu(quitc);
		textureMenu(back);


		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	

	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureB[0]);


	deleteTexture(&tabTextureW[1]);
	deleteTexture(&tabTextureB[1]);

	deleteTexture(&tabTextureW[2]);
	deleteTexture(&tabTextureB[2]);

	deleteTexture(&tabTextureW[3]);
	deleteTexture(&tabTextureB[3]);

	deleteTexture(&tabTextureW[4]);
	deleteTexture(&tabTextureB[4]);

	printf("nbc final pause vaut %d\n", nbC);


	return nbC;
}

int menuRules(Window win){

	std::vector<GLuint>tabTexture;

	for(int i=1; i<3; i++){
	char chemin[50];
	sprintf(chemin, "./src/rules/%d.png", i);

	tabTexture.push_back(initializeTexure(chemin));
	}

	

	Rectangle rectBack(65., 2., 12., 3.);


	Choice back(rectBack, tabTexture[0], tabTexture[1]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(back);

	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/rules/background.png");

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

					case SDLK_RETURN:
					printf("enter push");
					nbC=0;

					quit = 1;
					printf("\n");
					break;

				}	
			break;

			case SDL_MOUSEBUTTONDOWN:

				
				if(isIn(back.rectangle, e.button, win)){
					nbC=0;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in back");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(back.rectangle, e.motion, win)){
				selected = tabChoice[0];	
			}else {
				selected = tabChoice[1];
			}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureBackground(menu, win);

		
		textureMenu(back);


		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	

	deleteTexture(&menu);

	deleteTexture(&tabTexture[0]);
	deleteTexture(&tabTexture[1]);

	printf("nbc final rules vaut %d\n", nbC);
	return nbC;
}

int menuSettings(Window win){

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<2; i++){
	char chemin[50];
	sprintf(chemin, "./src/settings/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureC;

	for(int i=1; i<2; i++){
	char chemin[50];
	sprintf(chemin, "./src/settings/%dbis.png", i);

	tabTextureC.push_back(initializeTexure(chemin));
	}

	

	Rectangle rectBack(65., 2., 12., 3.);


	Choice back(rectBack, tabTextureW[0], tabTextureC[0]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(back);

	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/settings/background.png");

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

					case SDLK_RETURN:
					printf("enter push");
					nbC=0;

					quit = 1;
					printf("\n");
					break;

				}	
			break;

			case SDL_MOUSEBUTTONDOWN:

				
				if(isIn(back.rectangle, e.button, win)){
					nbC=0;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in back");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(back.rectangle, e.motion, win)){
				selected = tabChoice[0];	
			}else {
				selected = tabChoice[1];
			}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureBackground(menu, win);

		
		textureMenu(back);


		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	

	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureC[0]);

	printf("nbc final settings vaut %d\n", nbC);



	return nbC;
}

int menuVictory(Window win){

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<3; i++){
	char chemin[50];
	sprintf(chemin, "./src/victory/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureC;

	for(int i=1; i<3; i++){
	char chemin[50];
	sprintf(chemin, "./src/victory/%dbis.png", i);

	tabTextureC.push_back(initializeTexure(chemin));
	}
	

	Rectangle rectMenu(3., 2., 14., 3.);
	Rectangle rectQuit(65., 1., 12., 4.);


	
	Choice menuc(rectMenu, tabTextureW[0], tabTextureC[0]);
	Choice quitc(rectQuit, tabTextureW[1], tabTextureC[1]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(menuc);
	tabChoice.push_back(quitc);
	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/victory/background.png");
	// menu = initializeTexure("./src/victoryfond.png");


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

					case SDLK_LEFT:
					if(nbC>0){
						nbC-=1;
						printf("nbC vaut :%d \n", nbC);
						
					}else{
						nbC=1;
						printf("nbC vaut :%d \n", nbC);
					}
					selected = tabChoice[nbC];


					break;

					case SDLK_RIGHT:
					if(nbC<1){
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

				if(isIn(menuc.rectangle, e.button, win)){
					nbC=0;
					

					quit = 1;

					printf("nbC vaut :%d \n", nbC);
					printf("click is in menu");

					printf("\n");
				}
				else if(isIn(quitc.rectangle, e.button, win)){
					nbC=1;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in quit");
					printf("\n");
				}
				else {
					
				}
			break;

			case SDL_MOUSEMOTION :
		
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(menuc.rectangle, e.motion, win)){
					selected = tabChoice[0];
			}
			else if(isOver(quitc.rectangle, e.motion, win)){
				selected = tabChoice[1];
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

		textureMenu(menuc);
		textureMenu(quitc);

		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	


	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureC[0]);


	deleteTexture(&tabTextureW[1]);
	deleteTexture(&tabTextureC[1]);

	printf("nbc final victory vaut %d\n", nbC);


	return nbC;

}

int menuGameOver(Window win){

	std::vector<GLuint>tabTextureW;

	for(int i=1; i<4; i++){
	char chemin[50];
	sprintf(chemin, "./src/gameover/%d.png", i);

	tabTextureW.push_back(initializeTexure(chemin));
	}

	std::vector<GLuint>tabTextureC;

	for(int i=1; i<4; i++){
	char chemin[50];
	sprintf(chemin, "./src/gameover/%dbis.png", i);

	tabTextureC.push_back(initializeTexure(chemin));
	}
	

	Rectangle rectMenu(3., 2., 14., 3.);
	Rectangle rectRetry(32., 2., 15., 3.);
	Rectangle rectQuit(65., 1., 12., 4.);


	
	Choice menuc(rectMenu, tabTextureW[0], tabTextureC[0]);
	Choice retryc(rectRetry, tabTextureW[1], tabTextureC[1]);
	Choice quitc(rectQuit, tabTextureW[2], tabTextureC[2]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(menuc);
	tabChoice.push_back(retryc);
	tabChoice.push_back(quitc);
	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/victory/background.png");
	//menu = initializeTexure("./src/gameoverfond.png");


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

					case SDLK_LEFT:
					if(nbC>0){
						nbC-=1;
						printf("nbC vaut :%d \n", nbC);
						
					}else{
						nbC=2;
						printf("nbC vaut :%d \n", nbC);
					}
					selected = tabChoice[nbC];


					break;

					case SDLK_RIGHT:
					if(nbC<2){
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

				if(isIn(menuc.rectangle, e.button, win)){
					nbC=0;
					

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("click is in menu");
					printf("\n");
				}
				else if(isIn(retryc.rectangle, e.button, win)){
					nbC=1;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in retry");
					printf("\n");
				} else if(isIn(quitc.rectangle, e.button, win)){
					nbC=2;

					quit = 1;
					printf("nbC vaut :%d \n", nbC);
					printf("clicks is in quit");
					printf("\n");
				
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
		
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(menuc.rectangle, e.motion, win)){
					selected = tabChoice[0];
			}
			else if(isOver(retryc.rectangle, e.motion, win)){
				selected = tabChoice[1];
			} else if(isOver(quitc.rectangle, e.motion, win)){
				selected = tabChoice[2];
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

		textureMenu(menuc);
		textureMenu(retryc);
		textureMenu(quitc);

		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	


	deleteTexture(&menu);

	deleteTexture(&tabTextureW[0]);
	deleteTexture(&tabTextureC[0]);


	deleteTexture(&tabTextureW[1]);
	deleteTexture(&tabTextureC[1]);

	deleteTexture(&tabTextureW[2]);
	deleteTexture(&tabTextureC[2]);

	printf("nbc final gameover vaut %d\n", nbC);


	return nbC;

}

int menuFinal(Window win){

	std::vector<GLuint>tabTexture;

	for(int i=1; i<3; i++){
	char chemin[50];
	sprintf(chemin, "./src/final/%d.png", i);

	tabTexture.push_back(initializeTexure(chemin));
	}

	

	Rectangle rectBack(65., 1., 12., 4.);


	Choice back(rectBack, tabTexture[0], tabTexture[1]);


	int nbC = 0;

	std::vector<Choice>tabChoice;

	tabChoice.push_back(back);

	

	Choice selected = tabChoice[nbC];


	int quit = 0;
	SDL_Event e;

	
	GLuint menu;
	menu = initializeTexure("./src/final/background.png");

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

					case SDLK_RETURN:
					printf("enter push");
					nbC=0;

					quit = 1;
					printf("\n");
					break;

				}	
			break;

			case SDL_MOUSEBUTTONDOWN:

				
				if(isIn(back.rectangle, e.button, win)){
					nbC=0;
					printf("nbC vaut :%d \n", nbC);

					quit = 1;
					printf("clicks is in back");
					printf("\n");
				} else {
					
				}
			break;

			case SDL_MOUSEMOTION :
			printf("x vaut : %d\ny vaut: %d\n\n", mapWindowToGLcoordinateX(e.motion.x, win), mapWindowToGLcoordinateY(e.motion.y, win));
			

			if(isOver(back.rectangle, e.motion, win)){
				selected = tabChoice[0];	
			}else {
				selected = tabChoice[1];
			}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		textureBackground(menu, win);

		
		textureMenu(back);


		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}	

	deleteTexture(&menu);

	deleteTexture(&tabTexture[0]);
	deleteTexture(&tabTexture[1]);

	printf("nbc final final vaut %d\n", nbC);
	return nbC;
}



bool isOver(Rectangle choix, SDL_MouseMotionEvent over, Window win){
	return(choix.getPosX()<=mapWindowToGLcoordinateX(over.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(over.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(over.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(over.y, win));
}

bool isIn(Rectangle choix, SDL_MouseButtonEvent click, Window win){
	
	return(choix.getPosX()<=mapWindowToGLcoordinateX(click.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(click.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(click.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(click.y, win));
}




