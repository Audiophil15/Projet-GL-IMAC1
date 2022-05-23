#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <vector>


#include "block.h"
#include "string"


std::vector<Block> mapFromFile(std::string namefile){
	std::vector<Block> myblocks;

	int r;
	FILE* file = fopen(namefile.c_str() , "r");


	int v, d1, d2, d3, d4;
	do {
	v = 0;
	v += fscanf(file, "%d", &d1);
	v += fscanf(file, "%d", &d2);
	v += fscanf(file, "%d", &d3);
	v += fscanf(file, "%d", &d4);
	if (v == 4){
		Block blocks(d1, d2, d3, d4 );
		//myblocks[i++] = rect;
		myblocks.push_back(blocks);
		}
	}
	while (v == 4);

	return myblocks;

}