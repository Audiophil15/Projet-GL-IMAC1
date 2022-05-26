#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include "menu.h"

#include "graphics.h"
#include "menuChoice.h"
#include "rectangle.h"
#include "window.h"

int menu(Window win, std::string background, std::vector<std::string> choices, std::vector<Rectangle> boxes){

	int choice;
	GLuint bg = initializeTexure(background.c_str());

	std::vector<Choice>tabChoices;

	char pathW[50];
	char pathB[50];
	GLuint texW, texB;
	for(int i=0; i<choices.size(); i++){
		sprintf(pathW, "./src/%s-bg.png", choices[i].c_str());
		sprintf(pathB, "./src/%s-fg.png", choices[i].c_str());
		// printf("%s\n", pathW);//debug
		texW = initializeTexure(pathW);
		texB = initializeTexure(pathB);
		Choice c(boxes[i], texW, texB);
		tabChoices.push_back(c);
	}

	int nbC = 0;

	Choice selected = tabChoices[nbC];

	int quit = 0;
	SDL_Event e;

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
						}else{
							nbC=choices.size()-1;
						}
						selected = tabChoices[nbC];
					break;

					case SDLK_DOWN:
						nbC = (nbC+1)%choices.size();
						selected = tabChoices[nbC];
					break;

					case SDLK_RETURN:
						quit = 1;
					break;

				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				for (int i=0; i<tabChoices.size(); i++){
					if (clickIn(tabChoices[i].rectangle, e.button, win)){
						nbC = i;
						quit = 1;
					}
				}
			break;

			case SDL_MOUSEMOTION :
				for (int i=0; i<tabChoices.size(); i++){
					if (hover(tabChoices[i].rectangle, e.motion, win)){
						selected = tabChoices[i];
					}
				}

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		textureBackground(bg, win);

		for (Choice c:tabChoices){
			textureMenu(c);
		}
		textureMenuTop(selected);


		SDL_GL_SwapWindow(win.SDLWindow);

	}

	deleteTexture(&bg);
	for (int i=0; i<tabChoices.size(); i++){
		deleteTexture(&(tabChoices[i].textureBack));
		deleteTexture(&(tabChoices[i].textureFront));
	}

	return nbC;


}


int mainMenu(Window win){
	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("play");
	choices.push_back("rules");
	choices.push_back("options");
	choices.push_back("quit");

	Rectangle rectPlay(65.,33., 10., 3.);
	Rectangle rectRules(62., 28., 13., 3.);
	Rectangle rectOptions(57.,23., 18., 3.);
	Rectangle rectQuit(65., 17., 10., 4.);
	rects.push_back(rectPlay);
	rects.push_back(rectRules);
	rects.push_back(rectOptions);
	rects.push_back(rectQuit);

	choice = menu(win, "./src/background-mainMenu.png", choices, rects);

	return choice;
}



int choiceLevel(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("paris");
	choices.push_back("rome");
	choices.push_back("tokyo");
	choices.push_back("back");

	Rectangle rectParis(4.,17., 21., 11.);
	Rectangle rectRome(29., 17., 21., 11.);
	Rectangle rectTokyo(54.,17., 21., 11.);
	Rectangle rectBack(65., 2., 12., 3.);
	rects.push_back(rectParis);
	rects.push_back(rectRome);
	rects.push_back(rectTokyo);
	rects.push_back(rectBack);

	choice = menu(win, "./src/background-levelChoice.png", choices, rects);

	return (choice+1)%4-1;
}

int menuPause(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("backtogame");
	choices.push_back("rules");
	choices.push_back("options");
	choices.push_back("quit");
	choices.push_back("back");

	Rectangle rectBackToGame(45.,33., 30., 3.);
	Rectangle rectRules(62., 28., 13., 3.);
	Rectangle rectOptions(57.,23., 18., 3.);
	Rectangle rectQuit(65., 17., 10., 4.);
	Rectangle rectBack(65., 2., 12., 3.);

	rects.push_back(rectBackToGame);
	rects.push_back(rectRules);
	rects.push_back(rectOptions);
	rects.push_back(rectQuit);
	rects.push_back(rectBack);


	choice = menu(win, "./src/background-pause.png", choices, rects);

	return (choice+1)%5-1;

}

int menuRules(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("back");

	Rectangle rectBack(65., 2., 12., 3.);
	rects.push_back(rectBack);

	choice = menu(win, "./src/background-rules.png", choices, rects);

	return choice;
}

int menuSettings(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("back");

	Rectangle rectBack(65., 2., 12., 3.);
	rects.push_back(rectBack);

	choice = menu(win, "./src/background-settings.png", choices, rects);

	return choice;
}

int menuVictory(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("back");
	choices.push_back("quit");

	Rectangle rectMenu(3., 2., 14., 3.);
	Rectangle rectQuit(65., 1., 12., 4.);
	rects.push_back(rectMenu);
	rects.push_back(rectQuit);

	choice = menu(win, "./src/background-victory.png", choices, rects);

	return choice;
}

int menuGameOver(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("menu");
	choices.push_back("retry");
	choices.push_back("quit");

	Rectangle rectMenu(3., 2., 14., 3.);
	Rectangle rectRetry(32., 2., 15., 3.);
	Rectangle rectQuit(65., 1., 12., 4.);
	rects.push_back(rectMenu);
	rects.push_back(rectRetry);
	rects.push_back(rectQuit);

	choice = menu(win, "./src/background-gameOver.png", choices, rects);

	return choice;
}

int menuFinal(Window win){

	int choice;
	std::vector<std::string>choices;
	std::vector<Rectangle> rects;

	choices.push_back("back");

	Rectangle rectBack(65., 2., 12., 3.);
	rects.push_back(rectBack);

	choice = menu(win, "./src/background-final.png", choices, rects);

	return choice;
}



bool hover(Rectangle choix, SDL_MouseMotionEvent over, Window win){
	return(choix.getPosX()<=mapWindowToGLcoordinateX(over.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(over.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(over.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(over.y, win));
}

bool clickIn(Rectangle choix, SDL_MouseButtonEvent click, Window win){

	return(choix.getPosX()<=mapWindowToGLcoordinateX(click.x, win) && choix.getPosY()<=mapWindowToGLcoordinateY(click.y, win) && (choix.getPosX()+choix.getWidth())>=mapWindowToGLcoordinateX(click.x, win) && (choix.getPosY()+choix.getHeight())>=mapWindowToGLcoordinateY(click.y, win));
}




