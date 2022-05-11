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
	public:
		glm::vec2 position;
		glm::vec2 size;
		ColorRGB color;

	public:

		// Constructors
		Rectangle();
		Rectangle(double pos, double size);
		Rectangle(double x, double y, double w, double h);
		Rectangle(double x, double y, double w, double h, double r, double g, double b);

		void draw();
		double getPosX();
		double getPosY();
		double getWidth();
		double getHeight();
		double getCenterX();
		double getCenterY();
		void props();
};

#endif