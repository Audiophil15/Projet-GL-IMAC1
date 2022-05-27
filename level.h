#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "block.h"
#include "camera.h"
#include "music.h"
#include "quadtree.h"
#include "portail.h"
#include "string"
#include "window.h"

class Level{

	private :
		std::vector<Block> map;
		std::vector<Block> localEnv;
		std::vector<Block*> characters;
		std::vector<Portail> exits;
		Quadtree platformsTree;
		Camera camera;
		int currentPlayerIndex;
		Block* currentPlayer;

		


		std::vector<Block> mapFromFile(std::string filename);
		std::vector<Block*> charactersFromFile(std::string filename);
		Quadtree quadtreeFromFile(std::string filename);
		std::vector<Portail> portailsFromFile(std::string filename);

		// std::string musicFromFile(std::string filename);


	public :

		Level();
		Level(std::string filename);

		void manageEvent(SDL_Event);
		void display(Window, std::string filename);
		void switchCharacter();
		void updateCamera(Window, std::string filename);
		void updateLocalEnv();
		// Music music;	

		Block* getCurrentPlayer();
		void updatePlayer();
		double getZoom(std::string filename);
		glm::vec2 getBornes(std::string filename);
		int foundPortail();
		int nextLevel();
		int gameOver();

};


#endif