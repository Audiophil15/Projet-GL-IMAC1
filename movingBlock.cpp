#include <SDL2/SDL.h>

#include <math.h>

#include "rectangle.h"
#include "movingBlock.h"

movingBlock::movingBlock():Block(), finalPosition({0,0}){}
movingBlock::movingBlock(double x, double y, double xmax, double ymax, double w, double h):Block(x, y, w, h), initialPosition({x, y}), finalPosition({xmax, ymax}){};
movingBlock::movingBlock(double x, double y, double xmax, double ymax, double w, double h, double r, double g, double b):Block(x, y, w, h, r, g, b), initialPosition({x, y}), finalPosition({xmax,ymax}){}
movingBlock::movingBlock(double x, double y, double xmax, double ymax, double w, double h, float adh, int accX, int accY, double r, double g, double b):Block(x, y, w, h, adh, accX, accY, r, g, b), initialPosition({x, y}), finalPosition({xmax, ymax}){};
movingBlock::movingBlock(double x, double y, double xmax, double ymax, double w, double h, float adh, int accX, int accY, double r, double g, double b, float j):Block(x, y, w, h, adh, accX, accY, r, g, b, j), initialPosition({x, y}), finalPosition({xmax, ymax}){}

void movingBlock::updateAcceleration(){

	this->position.x = this->initialPosition.x+(this->finalPosition.x-this->initialPosition.x)*sin(2*M_PI*0.5*SDL_GetTicks64()/1000.0);
	this->position.y = this->initialPosition.y+(this->finalPosition.y-this->initialPosition.y)*sin(2*M_PI*0.5*SDL_GetTicks64()/1000.0);


	// this->acc.x = -4*M_PI*xt;//-(this->finalPosition.x-this->position.x)*sin(dt)/2;
	// this->acc.y = -4*M_PI*yt;//-(this->finalPosition.y-this->position.y)*sin(dt)/2;

}
