#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "block.h"

Block::Block():Rectangle{0,0,25,25,1,1,1}, speed({0,0}), acc({0,0}), adherence(1){}

Block::Block(float adh):Rectangle{0,0,25,25,1,1,1}, speed({0,0}), acc({0,0}), adherence(adh){}

Block::Block(double pos, double size):Rectangle{pos,pos,size,size,1,1,1}, speed({0,0}), acc({0,0}), adherence(1){}

Block::Block(double pos, double size, float adh):Rectangle{pos,pos,size,size,1,1,1}, speed({0,0}), acc({0,0}), adherence(adh){}

Block::Block(double x, double y, double w, double h):Rectangle{x,y,w,h,1,1,1}, speed({0,0}), acc({0,0}), adherence(1){}

Block::Block(double x, double y, double w, double h, float adh):Rectangle{x,y,w,h,1,1,1}, speed({0,0}), acc({0,0}), adherence(adh){}

Block::Block(double x, double y, double w, double h, double r, double g, double b):Rectangle{x,y,w,h,r,g,b}, speed({0,0}), acc({0, 0}), adherence(1){}

Block::Block(double x, double y, double w, double h, float adh, double r, double g, double b):Rectangle{x,y,w,h,r,g,b}, speed({0,0}), acc({0, 0}), adherence(adh){}

Block::Block(double x, double y, double w, double h, float adh, int accX, int accY):Rectangle{x,y,w,h,1,1,1}, speed({0,0}), acc({accX,accY}), adherence(adh){}

Block::Block(double x, double y, double w, double h, float adh, int accX, int accY, double r, double g, double b):Rectangle{x,y,w,h,r,g,b}, speed({0,0}), acc({accX, accY}), adherence(adh){}


void Block::moveto(int x, int y){
	this->position.x = x;
	this->position.y = y;
}

void Block::moverel(int dx, int dy){
	this->position.x += dx;
	this->position.y += dy;
}

void Block::moveto(glm::vec2 position){
	this->position.x = position.x;
	this->position.y = position.y;
}

void Block::moverel(glm::vec2 dv){
	this->position.x += dv.x;
	this->position.y += dv.y;
}

void Block::jump(){
	if (!this->isJumping){
		this->speed.y = 23.0; //25
		this->isJumping = 1;
	}
}




void Block::updatePosition(std::vector<Block> environment, double dt){
	Block b;

	this->acc.x = 100*(this->isMovingRight-this->isMovingLeft - this->speed.x*this->adherence*(2-(this->isMovingLeft || this->isMovingRight)));

	this->speed.x += this->acc.x*dt;
	this->speed.y += this->acc.y*dt;
	this->position.x += this->speed.x*dt;
	this->position.y += this->speed.y*dt;

	for (Block b : environment){
		//printf("Collision : %d", this->collidesWith(b)); //DEBUG

		if (this->collidesWith(b)){
			this->position.y -= this->speed.y*dt;
			this->position.x -= this->speed.x*dt;

			//printf(" : "); //DEBUG

			this->position.y += this->speed.y*dt;
			if (this->collidesWith(b)){
			this->position.y -= this->speed.y*dt;
				speed.y = 0;
				if (this->isOver(b)){
					this->isJumping = 0;
				}
			}

			this->position.x += this->speed.x*dt;
			if (this->collidesWith(b)){
			this->position.x -= this->speed.x*dt;
				speed.x = 0;
			}
		}
		printf("\n");

	}

}

int Block::collidesWith(Block b){
	return !(this->getPosX() > b.getPosX()+b.getWidth() || this->getPosX()+this->getWidth() < b.getPosX() || this->getPosY() > b.getPosY()+b.getHeight() || this->getPosY()+this->getHeight() < b.getPosY());
}

int Block::isHorizontalTo(Block b){
	return (this->getPosY()<b.getPosY()+b.getHeight() && this->getPosY()+this->getHeight() > this->getPosY());
}

int Block::isVerticalTo(Block b){
	return (this->getPosX()<b.getPosX()+b.getWidth() && this->getPosX()+this->getWidth() > this->getPosX());
}

int Block::isLeftTo(Block b){
	return (this->getCenterX()<b.getCenterX());
}

int Block::isRightTo(Block b){
	return (this->getCenterX()>b.getCenterX());
}

int Block::isOver(Block b){
	return (this->getCenterY()>b.getCenterY());
}

int Block::isUnder(Block b){
	return (this->getCenterY()<b.getCenterY());
}

