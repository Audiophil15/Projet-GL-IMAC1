#include "block.h"

void Block::moveto(int x, int y){
	this->position.x = x;
	this->position.y = y;
}

void Block::moverel(int dx, int dy){
	this->position.x += dx;
	this->position.y += dy;
}

int Block::collidesWith(Block b){
	if (this->getPosX() > b.getPosX()+b.getWidth() || this->getPosX()+this->getWidth() < b.getPosX() || this->getPosY() > b.getPosY()+b.getHeight() || this->getPosY()+this->getHeight() < b.getPosY()){
		return 0;
	}
	return 1;
}

int Block::collidesWith(Rectangle b){
	if (this->getPosX() > b.getPosX()+b.getWidth() || this->getPosX()+this->getWidth() < b.getPosX() || this->getPosY() > b.getPosY()+b.getHeight() || this->getPosY()+this->getHeight() < b.getPosY()){
		return 0;
	}
	return 1;
}