#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

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
	//this->getZoom(filename);
	// this->platformsTree.initialize(this->map);
	this->currentPlayer = this->characters[this->currentPlayerIndex];
}

std::vector<Block> Level::mapFromFile(std::string filename){
	std::vector<Block> blocks;

	FILE* file = fopen(filename.c_str() , "r");
	char p;
	double r=1;
	double g=1;
	double b=1;
	double v, d1, d2, d3, d4;
	//int zoom = 1;
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

			/*case 'z' :
				sscanf(line, "%*s %d", &zoom);
			break;*/

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	do {
		v = 0;
		v += fscanf(file, "%lf", &d1);
		v += fscanf(file, "%lf", &d2);
		v += fscanf(file, "%lf", &d3);
		v += fscanf(file, "%lf", &d4);


		if (v == 4){
			Block block(d1, d2, d3, d4,r,g,b);
			blocks.push_back(block);
			}
	} while (v == 4);

	return blocks;

}

std::vector<Block*> Level::charactersFromFile(std::string filename){
	std::vector<Block*> characters;

	FILE* file = fopen(filename.c_str() , "r");
	char p;
	double zoom = 1;
	double r=1;
	double g=1;
	double b=1;
	double x=0;
	double y=0;
	float j=21.;
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
			case 'z' :
				sscanf(line, "%*s %lf", &zoom);
			break;

			case 'r' :
				sscanf(line, "%*s %lf %lf %lf %lf %lf %lf %lf %f", &x, &y, &sizeX, &sizeY, &r, &g, &b, &j);
				character = new Block(x, y, sizeX, sizeY, 0.09, 0., -58.8, r,g,b,j);
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


double Level::getZoom(std::string filename){
	double zoom = 1;

	FILE* file = fopen(filename.c_str() , "r");
	char parameter[10];
	char line[50];
	char copy[50];

	do{
		fscanf(file, "%[^\n] ", line);
		strcpy(copy, line);
		strcpy(parameter, strtok(copy, " "));

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

glm::vec2 Level::getBornes(std::string filename){
	/*int xmax = 100;
	int ymax = 50;*/
	glm::vec2 border;
	border.x = 150;
	border.y = 50;

	FILE* file = fopen(filename.c_str() , "r");
	char parameter[10];
	char line[50];
	char copy[50];

	do{
		fscanf(file, "%[^\n] ", line);
		strcpy(copy, line);
		strcpy(parameter, strtok(copy, " "));

		switch(parameter[0]){
			case 'b' : { 
				sscanf(line, "%*s %f %f" , &border.x, &border.y);
			}
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));
	
	return border;
}

void Level::updateCamera(Window window, std::string filename){ // DEPLACER DANS CAMERA.CPP
	glm::vec2 bornes;
	this->camera.setPosition(this->currentPlayer->getPosition());
	this->camera.setX(std::max(0.f, this->camera.getX()-(window.baseW*window.zoom)/2));
	this->camera.setY(std::max(0.f, this->camera.getY()-(window.baseH*window.zoom)/5));

	bornes = this->getBornes(filename);

	if(camera.getX() > bornes.x-window.baseW*window.zoom){
		camera.setX(bornes.x-window.baseW*window.zoom);
	}

	if(camera.getY() > bornes.y-window.baseH*window.zoom){
		camera.setY(bornes.y-window.baseH*window.zoom);
	}


}


Block* Level::getCurrentPlayer(){
	return this->currentPlayer;
}

void Level::updateLocalEnv(){
	// DEBUG
	this->localEnv = this->map;//this->platformsTree.findChild(this->currentPlayer->getPosX(), this->currentPlayer->getPosY())
	//this->localEnv.push_back(*(this->characters[0]));
	//this->localEnv.push_back(*(this->characters[1]));
	
	for(int i=0; i<this->characters.size(); i++){
		if(i!=this->currentPlayerIndex){

		this->localEnv.push_back(*(this->characters[i]));
	}
	}
}

void Level::display(Window window, std::string filename){
	this->updateCamera(window, filename);

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
	//this->updatePlayer();
	/*for (Block* b:this->characters){
		this->updatePlayer();
	}*/
}

void Level::manageEvent(SDL_Event e){
	switch (e.type){
		case SDLK_TAB :
			printf("test");
			this->switchCharacter();
		break;

		default :
		break;

	}
}