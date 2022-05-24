#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "block.h"
#include "camera.h"
#include "quadtree.h"
#include "string"
#include "window.h"

class Level{

	private :
		std::vector<Block> map;
		std::vector<Block> localEnv;
		std::vector<Block*> characters;
		Quadtree platformsTree;
		Camera camera;

		int currentPlayerIndex;
		Block* currentPlayer;

		std::vector<Block> mapFromFile(std::string filename);
		std::vector<Block*> charactersFromFile(std::string filename);
		Quadtree quadtreeFromFile(std::string filename);

	public :

		Level();
		Level(std::string filename);

		void manageEvent(SDL_Event);
		void display(Window);

		void switchCharacter();
		void updateCamera(Window);
		void updateLocalEnv();

		Block* getCurrentPlayer();
		void updatePlayer();
		double getZoom(std::string filename);

};


#endif