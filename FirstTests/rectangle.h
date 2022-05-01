#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/vec2.hpp>

#include "color.h"
/*
Contains the declaration of the Rectangle class, parent class of the herited class Block.
The Rectangle only defines position, size and color. Movements and other actions belong to the Block class.
*/

class Rectangle{
		// int x, y, w, h;
	protected:
		glm::vec2 position;
		glm::vec2 size;
		ColorRGB color;

	public:

		// Constructors
		Rectangle();
		Rectangle(int pos, int size);
		Rectangle(int x, int y, int w, int h);
		Rectangle(int x, int y, int w, int h, double r, double g, double b);

		void draw();
		void props();
		void setColor(float r, float g, float b);
		int getPosX();
		int getPosY();
		int getWidth();
		int getHeight();
};

#endif