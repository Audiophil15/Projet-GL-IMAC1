#ifndef BLOCK_H
#define BLOCK_H

#include "rectangle.h"

class Block : public Rectangle {
	using Rectangle::Rectangle;
	public:
		void moveto(int x, int y);
		void moverel(int x, int y);
		int getPosX();
		int getPosY();
		int getwidth();
		int getheight();

		glm::vec2 getCenter();

};

#endif