#ifndef QUADTREE_H
#define QUADTREE_

#include "block.h"
#include <vector>


class Quadtree {
	public : 
	// Constructors
	Quadtree();
	Quadtree(int xmin, int ymin, int xmax, int ymax);

	private :
	std::vector<Block> myblocks;

	int xmin;
    int ymin;
    int xmax;
    int ymax;

	Quadtree *tl = nullptr; 
	Quadtree *bl = nullptr;
	Quadtree *tr = nullptr;
	Quadtree *br = nullptr;

	void insert(Block &b);
	void createChildren();
	void initialize(std::vector<Block> tabBlocks);
	bool isLeaf();
	bool isFilled();
	void insertInChildren(Block &b);
	void insertRight(Block &b);
	void insertLeft(Block &b);
};



#endif