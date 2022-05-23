#include "block.h"
#include <vector>
#include <queue>
#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

using namespace std;

Quadtree::Quadtree():Quadtree(0,0,0,0){}
Quadtree::Quadtree(int xmin, int ymin, int xmax, int ymax):xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax){}

std::vector<Block> Quadtree::findChild(Quadtree *tree, double x, double y){

		/*printf("xmax : %d", tree->xmax);
		printf("ymax : %d", tree->ymax);
		printf("xmin : %d", tree->xmin);
		printf("ymin : %d \n", tree->ymin);*/

	if(!tree->isLeaf()){

	if(x< (double) (tree->xmax + tree->xmin)/2){

		if(y< ((double)tree->ymax + (double) tree->ymin)/2){

		return tree->findChild(tree->bl, x,y);

		}else{
		return tree->findChild(tree->tl, x,y);
		}
	}else{
		if(y< ((double)tree->ymax + (double) tree->ymin)/2){
		return tree->findChild(tree->br, x,y);
		}else{
		return tree->findChild(tree->tr, x,y);
		}
	}
	}
	//printf("size : %ld", tree->blocks.size());
	//exit(0);
	//return blocks;
	return tree->blocks;
}

void Quadtree::insert(Block &b){
	// printf("%p|%p|%p|%p :: %d\n", this->bl, this->br, this->tl, this->tr, this->isLeaf()); // debug
	if(this->isLeaf()){
		if(this->isFilled()){
			this->createChildren();
			for(Block block : this->blocks){
				this->insert(block);
			}
			blocks.clear();
			this->insert(b);
		}else{
			this->blocks.push_back(b);
		}
	}else{
		this->insertInChildren(b);
	}
	this->render();

}

void Quadtree::insertInChildren(Block &b){
	if(b.getPosX()<=this->getCenterX()){
		if (b.getPosY()<=this->getCenterY()){
			this->bl->insert(b);
		}
		if (b.getPosY()+b.getHeight()>=this->getCenterY()){
			this->tl->insert(b);
		}
	}

	if(b.getPosX()+b.getWidth()>=this->getCenterX()){
		if (b.getPosY()<=this->getCenterY()){
			this->br->insert(b);
		}
		if (b.getPosY()+b.getHeight()>=this->getCenterY()){
			this->tr->insert(b);
		}
	}
}

void Quadtree::createChildren(){
	this->tl = new Quadtree(this->xmin, this->getCenterY(), this->getCenterX(), this->ymax);
	this->bl = new Quadtree(this->xmin, this->ymin, this->getCenterX(), this->getCenterY());
	this->tr = new Quadtree(this->getCenterX(), this->getCenterY(), this->xmax, this->ymax);
	this->br = new Quadtree(this->getCenterX(), this->ymin, this->xmax, this->getCenterY());
}

void Quadtree::render(){
	glColor3d(0,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex2d(this->xmin, this->ymin);
		glVertex2d(this->xmax, this->ymin);
		glVertex2d(this->xmax, this->ymax);
		glVertex2d(this->xmin, this->ymax);
	glEnd();
}

void Quadtree::breadth(){
	std::queue<Quadtree*> queue;
	queue.push(this);

	Quadtree* node;

	int n =0;
	while (!queue.empty()){
		// printf("%d!!", n++); //debug
		node = queue.front();
		queue.pop();
		node->render();
		if (!this->isLeaf()){
			queue.push(this->bl);
			queue.push(this->br);
			queue.push(this->tl);
			queue.push(this->tr);
		}
	}
}

void Quadtree::depth(int gldraw){
	// printf("depth call\n");
	/*glBegin(GL_LINE_LOOP);
		glVertex2d(this->xmin, this->ymin);
		glVertex2d(this->xmax-this->xmin, this->ymin);
		glVertex2d(this->xmax-this->xmin,  this->ymax-this->ymin);
		glVertex2d(this->xmin, this->ymax-this->ymin);
	glEnd();*/

	/*Block rect(this->xmin, this->ymin, this->xmax-this->xmin, this->ymax-this->ymin);
	rect.draw();*/
	if (!this->isLeaf()){
		this->bl->depth(gldraw);
		this->br->depth(gldraw);
		this->tl->depth(gldraw);
		this->tr->depth(gldraw);
	} else {
		/*Block rect(this->xmin, this->ymin, this->xmax-this->xmin, this->ymax-this->ymin);
		rect.draw();*/
		//rect.props();
		// printf("la taille du tableau : %ld \n", blocks.size());
		// for (Block b:this->blocks){
		// 	printf("%.2lf : %.2lf\n", b.getPosX(), b.getPosY());
		// }
		if (gldraw){
			this->render();
			// printf("xm : %d\nym : %d\nxM : %d\nyM : %d\n\n", this->xmin, this->ymin, this->xmax, this->ymax);
		}
	}
}


void Quadtree::initialize(std::vector<Block> tabBlocks){
	for(Block b : tabBlocks){
		this->insert(b);
	}
}

bool Quadtree::isLeaf(){
	return (this->tl==nullptr && this->bl==nullptr && this->tr==nullptr && this->br==nullptr);
}

bool Quadtree::isFilled(){
	return (blocks.size()>3);
}

int Quadtree::getCenterX(){
	return (this->xmax+this->xmin)/2;
}

int Quadtree::getCenterY(){
	return (this->ymax+this->ymin)/2;
}
