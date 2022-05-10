#include "rectangle.h"
#include "color.h"

#include <stdio.h>
#include <GL/gl.h>

Rectangle::Rectangle():position({0,0}), size({25,25}), color(ColorRGB(1,1,1)){}
Rectangle::Rectangle(int pos, int size):position({pos,pos}), size({size,size}), color(ColorRGB(1,1,1)){}
Rectangle::Rectangle(int x, int y, int w, int h): position({x,y}), size({w,h}), color(ColorRGB(1,1,1)){}
Rectangle::Rectangle(int x, int y, int w, int h, double r, double g, double b): position({x,y}), size({w,h}), color(ColorRGB(r,g,b)){}

void Rectangle::draw(){
	glColor3d(this->color.r, this->color.g, this->color.b);

	glBegin(GL_QUADS);
		glVertex2d(this->position.x, this->position.y);
		glVertex2d(this->position.x+this->size.x, this->position.y);
		glVertex2d(this->position.x+this->size.x, this->position.y+this->size.y);
		glVertex2d(this->position.x, this->position.y+this->size.y);
	glEnd();
}

void Rectangle::props(){
	printf("%g : %g : %g : %g\n",this->position.x, this->position.y, this->size.x, this->size.y);
	printf("%g : %g : %g\n", this->color.r, this->color.g, this->color.b);
}