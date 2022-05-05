#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "rectangle.h"

class Block : public Rectangle {
	using Rectangle::Rectangle;

	public:
		glm::vec2 speed;
		glm::vec2 acc;
		float adherence;
		int isMovingRight, isMovingLeft, isJumping;

	public:

		Block();
		Block(float adh);
		Block(double pos, double size);
		Block(double pos, double size, float adh);
		Block(double x, double y, double w, double h);
		Block(double x, double y, double w, double h, float adh);
		Block(double x, double y, double w, double h, double r, double g, double b);
		Block(double x, double y, double w, double h, float adh, double r, double g, double b);
		Block(double x, double y, double w, double h, float adh, int accX, int accY);
		Block(double x, double y, double w, double h, float adh, int accX, int accY, double r, double g, double b);

		void moveto(int x, int y);
		void moverel(int x, int y);
		void moveto(glm::vec2);
		void moverel(glm::vec2);
		int collidesWith(Block);
		int isOver(Block);
		int isInlinewith(Block);
		int isLeftTo(Block);
		int isRightTo(Block);
		int isOn(Block);

		void jump();
		void updatePosition(std::vector<Block> environment, double dt);

};

#endif