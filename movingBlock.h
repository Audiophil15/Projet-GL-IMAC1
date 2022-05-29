#ifndef MOVING_BLOCK_H
#define MOVING_BLOCK_H

#include <glm/vec2.hpp>

#include "block.h"

class movingBlock : public Block{
	using Block::Block;

	private :

		glm::vec2 initialPosition;
		glm::vec2 finalPosition;


	public :

		movingBlock();
		movingBlock(double x, double y, double xmax, double ymax, double w, double h);
		movingBlock(double x, double y, double xmax, double ymax, double w, double h, double r, double g, double b);
		movingBlock(double x, double y, double xmax, double ymax, double w, double h, float adh, int accX, int accY, double r, double g, double b);
		movingBlock(double x, double y, double xmax, double ymax, double w, double h, float adh, int accX, int accY, double r, double g, double b, float j);

		void updateAcceleration();

};

#endif