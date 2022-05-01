#ifndef BLOCK_H
#define BLOCK_H

#include "rectangle.h"

class Block : public Rectangle {
	using Rectangle::Rectangle;
	public:
		void moveto(int x, int y);
		void moverel(int x, int y);

		int collidesWith(Block b);
		int collidesWith(Rectangle b);
};

#endif