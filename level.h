#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "block.h"
#include "quadtree.h"
#include "string"

class Level : Scene {

	private :
		std::vector<Block> map;
		std::vector<Block> players;

		Block* currentPlayer;


	public :

		void manageEvent(SDL_Event);
		void display();

};

std::vector<Block> mapFromFile(std::string namefile);
std::vector<Block> creaWithFile(std::string namefile);
std::vector<Block> creaCharaWithFile(std::string namefile);
Quadtree leveltree(std::string namefile);
//void readColor(	char *file, double *r, double *g, double *b);
//void readColor(char *file, char c, double *r, double *g, double *b);

#endif