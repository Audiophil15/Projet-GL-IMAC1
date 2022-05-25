#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "level.h"

#include "block.h"
#include "camera.h"
#include "quadtree.h"

Level::Level(){}

Level::Level(std::string filename):currentPlayerIndex(0){
	this->map = this->mapFromFile(filename);
	// printf("after creation (%d) :\n", this->map.size()); // debug
	// for (Block b:this->map){
	// 	b.props();
	// }
	this->characters = this->charactersFromFile(filename);
	this->platformsTree = this->quadtreeFromFile(filename);
	// this->platformsTree.initialize(this->map);
	this->currentPlayer = this->characters[this->currentPlayerIndex];


	//music
	this->music = this->musicFromFile(filename);
	
}

std::vector<Block> Level::mapFromFile(std::string filename){
	std::vector<Block> blocks;

	FILE* file = fopen(filename.c_str() , "r");
	char p;
	double r=1;
	double g=1;
	double b=1;
	int v, d1, d2, d3, d4;
	int zoom = 1;
	char parameter[10];// = (char *) malloc( 10 * sizeof(char));

	char line[50];// = (char *) malloc( 50 * sizeof(char));
	char copy[50];// = (char *) malloc(strlen(line) + 1);

	char test[10];// = (char *) malloc( 10 * sizeof(char));

	do{
		fscanf(file, "%[^\n] ", line);
		strcpy(copy, line);
		strcpy(parameter, strtok(copy, " "));
		// printf("parameter :: %c\n", parameter[0]); //debug


		switch(parameter[0]){
			case 'c' :
				sscanf(line, "%*s %lf %lf %lf", &r, &g, &b);
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	do {
		v = 0;
		v += fscanf(file, "%d", &d1);
		v += fscanf(file, "%d", &d2);
		v += fscanf(file, "%d", &d3);
		v += fscanf(file, "%d", &d4);


		if (v == 4){
			Block block(d1*zoom, d2*zoom, d3*zoom, d4*zoom,r,g,b);
			blocks.push_back(block);
			}
	} while (v == 4);

	return blocks;

}

std::vector<Block*> Level::charactersFromFile(std::string filename){
	std::vector<Block*> characters;

	FILE* file = fopen(filename.c_str() , "r");
	char p;
	double r=1;
	double g=1;
	double b=1;
	double x=0;
	double y=0;
	double sizeX = 1;
	double sizeY = 1;
	Block* character;
	char parameter[10];
	char line[50];
	char copy[50];


	do{
		fscanf(file, "%[^\n] ", line);
		strcpy(copy, line);
		strcpy(parameter, strtok(copy, " "));
		// printf("%s\n", line);

		switch(parameter[0]){
			case 'r' :
				sscanf(line, "%*s %lf %lf %lf %lf %lf %lf %lf", &x, &y, &sizeX, &sizeY, &r, &g, &b);
				character = new Block(x, y, sizeX, sizeY, 0.025, 0., -58.8, r,g,b);
				characters.push_back(character);
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	return characters;

}

Quadtree Level::quadtreeFromFile(std::string filename){
	int xmin=0;
	int ymin=0;
	int xmax=0;
	int ymax=0;
	FILE* file = fopen(filename.c_str() , "r");
	char parameter[10];
	char line[50];
	char copy[50];

	do{
	fscanf(file, "%[^\n] ", line);
	strcpy(copy, line);
	strcpy(parameter, strtok(copy, " "));
	// printf("%s\n", line);

	switch(parameter[0]){
			case 'q' :
				sscanf(line, "%*s %d %d %d %d", &xmin, &ymin, &xmax, &ymax);
			break;

			default:
			break;
	}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));

	Quadtree tree(xmin, ymin, xmax, ymax);
	return tree;
}

//music from file
Mix_Music* Level::musicFromFile(std::string filename){

}




void Level::updateCamera(Window window){ // DEPLACER DANS CAMERA.CPP
	this->camera.setPosition(this->getCurrentPlayer()->getPosition());
	this->camera.setX(std::max(0.f, this->camera.getX()-window.baseW/2));
	this->camera.setY(std::max(0.f, this->camera.getY()-window.baseH/5));

}

Block* Level::getCurrentPlayer(){
	return this->currentPlayer;
}

void Level::updateLocalEnv(){
	// DEBUG
	this->localEnv = this->map;//this->platformsTree.findChild(this->currentPlayer->getPosX(), this->currentPlayer->getPosY());
}

void Level::display(Window window){
	//a deplacer (methode de camera)
	this->updateCamera(window);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glColor3f(1,0,0);
	// axis(window.baseW, window.baseH);

	glPushMatrix();
		glTranslatef(-this->camera.getX(), -this->camera.getY(), 0);
		// glColor3f(0,1,0);
		// axis(window.baseW, window.baseH);

		// this->currentPlayer->draw();
		for (Block* character:this->characters){
			character->draw();
		}
		for (Block b : this->localEnv){
			b.draw();
		}
		this->platformsTree.depth(1); //debug

	glPopMatrix();

	SDL_GL_SwapWindow(window.SDLWindow);

}

void Level::updatePlayer(){
	this->getCurrentPlayer()->moveFromInputs();
	this->getCurrentPlayer()->updatePosition(this->localEnv);
}

void Level::switchCharacter(){
	this->currentPlayerIndex = (this->currentPlayerIndex+1)%this->characters.size();
	this->currentPlayer = this->characters[this->currentPlayerIndex];
	for (Block* b:this->characters){

	}
}

void Level::manageEvent(SDL_Event e){
	switch (e.type){
		case 769 : // Code for SDL_KEYDOWN (only here ?)
			if (e.key.keysym.sym == SDLK_TAB){
				this->switchCharacter();
			}
		break;

		default :
		break;

	}
}

double Level::getZoom(std::string filename){
	double zoom = 1;

	FILE* file = fopen(filename.c_str() , "r");
	char parameter[10];// = (char *) malloc( 10 * sizeof(char));

	char line[50];// = (char *) malloc( 50 * sizeof(char));
	char copy[50];// = (char *) malloc(strlen(line) + 1);

	do{
		fscanf(file, "%[^\n] ", line);
		char * copy = (char *) malloc(strlen(line) + 1);
		strcpy(copy, line);
		strcpy(parameter, strtok(copy, " "));
		// printf("%s", line);

		switch(parameter[0]){
			case 'z' : {
				sscanf(line, "%*s %lf", &zoom);
			}
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	return zoom;
}