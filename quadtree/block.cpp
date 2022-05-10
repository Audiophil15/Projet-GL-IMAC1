#include "block.h"
#include <glm/vec2.hpp>


void Block::moveto(int x, int y){
	this->position.x = x;
	this->position.y = y;
}

void Block::moverel(int dx, int dy){
	this->position.x += dx;
	this->position.y += dy;
}

int Block::getPosX(){
	return this->position.x;
}

int Block::getPosY(){
	return this->position.y;
}

int Block::getwidth(){
	return this->size.x;
}

int Block::getheight(){
	return this->size.y;
}

glm::vec2 Block::getCenter(){
	glm::vec2 v(this->getPosX()+this->getheight()/2, this->getPosY()+this->getwidth()/2);
	return v;

}

