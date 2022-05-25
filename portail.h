#ifndef PORTAIL_H
#define PORTAIL_H

#include <SDL2/SDL.h>
#include <vector>
#include "rectangle.h"
#include "block.h"

class Portail : public Rectangle {
	using Rectangle::Rectangle;

	private:

	public:
    Portail(double x, double y, double w, double h, double r, double g, double b);

    int isExit(Block character); 

};

#endif