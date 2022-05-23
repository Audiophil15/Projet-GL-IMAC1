#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "block.h"
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

#endif