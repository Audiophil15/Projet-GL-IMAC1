#ifndef GAME_ENVIRONMENT_H
#define GAME_ENVIRONMENT_H

#include "level.h"
#include "window.h"

class GameEnvironment{

	private :
		// enum
		int quit;
		int gameloop;
		int gameOver;
		Level level;

	public :
		Window window;

		GameEnvironment();
		void manageEvents();
		void loadLevel(int level);
		void startGame();
		void play(int level);
		// changeToMenu

};

#endif