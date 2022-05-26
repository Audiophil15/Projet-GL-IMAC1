#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <vector>
#include "rectangle.h"

class Block : public Rectangle {
	using Rectangle::Rectangle;

	private:
		glm::vec2 speed;
		glm::vec2 acc;
		float adherence;
		float jumpValue;
		int isMovingRight, isMovingLeft, isJumping;
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

	public:

		Block();
		Block(double x, double y, double w, double h);
		Block(double x, double y, double w, double h, double r, double g, double b);
		Block(double x, double y, double w, double h, float adh, int accX, int accY, double r, double g, double b);
		Block(double x, double y, double w, double h, float adh, int accX, int accY, double r, double g, double b, float j);

		void moveto(int x, int y);
		void moverel(int x, int y);
		void moveto(glm::vec2);
		void moverel(glm::vec2);
		int collidesWith(Block b);
		int isHorizontalTo(Block b);
		int isVerticalTo(Block b);
		int isLeftTo(Block b);
		int isRightTo(Block b);
		int hover(Block b);
		int isUnder(Block b);


		void jump();
		void stop();
		void updatePosition(std::vector<Block> environment);
		void moveFromInputs();
		void printInputs();
		void drawSelect();

};

#endif