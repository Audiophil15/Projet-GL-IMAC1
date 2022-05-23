#ifndef QUADTREE_H
#define QUADTREE_H

#include "block.h"
#include <vector>


class Quadtree {

	private :
		//std::vector<Block> myblocks;

		int xmin;
		int ymin;
		int xmax;
		int ymax;

	public :
		Quadtree *tl = nullptr;
		Quadtree *bl = nullptr;
		Quadtree *tr = nullptr;
		Quadtree *br = nullptr;

		std::vector<Block> blocks;

		void createChildren();
		void insert(Block &b);
		bool isLeaf();
		bool isFilled();
		void insertInChildren(Block &b);
		void insertRight(Block &b);
		void insertLeft(Block &b);
		int getCenterX();
		int getCenterY();


		// Constructors
		Quadtree();
		Quadtree(int xmin, int ymin, int xmax, int ymax);

		void initialize(std::vector<Block> tabBlocks);
		void depth(int gldraw);
		void breadth();

		std::vector<Block> findChild(Quadtree *tree, double x, double y);
		void render();

};



#endif