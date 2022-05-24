#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

#include "block.h"

class Quadtree {

	private :
		//std::vector<Block> myblocks;

		int xmin;
		int ymin;
		int xmax;
		int ymax;
		Quadtree *tl = nullptr;
		Quadtree *bl = nullptr;
		Quadtree *tr = nullptr;
		Quadtree *br = nullptr;
		std::vector<Block> blocks;

		bool isLeaf();
		bool isFilled();
		void insertInChildren(Block &b);
		void insertRight(Block &b);
		void insertLeft(Block &b);
		void createChildren();
		int getCenterX();
		int getCenterY();

	public :

		// Constructors
		Quadtree();
		Quadtree(int xmin, int ymin, int xmax, int ymax);

		void initialize(std::vector<Block> tabBlocks);
		void insert(Block &b);
		void depth(int gldraw);
		std::vector<Block> findChild(double x, double y);
		void render();

};



#endif