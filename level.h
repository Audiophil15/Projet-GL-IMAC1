#ifndef LEVEL_H
#define LEVEL_H
#include <SDL2/SDL_image.h>
#include <string>
#include "block.h"
#include "camera.h"
#include "music.h"
#include "quadtree.h"
#include "portail.h"
#include "string"
#include "window.h"
#include "graphics.h"

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
		// Music levelMusic;


		std::vector<Block> mapFromFile(std::string filename);
		std::vector<Block*> charactersFromFile(std::string filename);
		Quadtree quadtreeFromFile(std::string filename);
		std::vector<Portail> portailsFromFile(std::string filename);

		Music musicFromFile(std::string filename);


	public :

		Level();
		Level(std::string filename, std::string bgName);

		void manageEvent(SDL_Event);
		void display(Window, std::string filename);
		void switchCharacter();
		void updateCamera(Window, std::string filename);
		void updateLocalEnv();
			

		Block* getCurrentPlayer();
		void updatePlayer();
		double getZoom(std::string filename);
		glm::vec2 getBornes(std::string filename);
		int foundPortail();
		int nextLevel();
		int gameOver();
		GLuint background;
		void setBackground(int bgName, Window window);

		Music music;
		void setMusic(std::string filename);

};


#endif