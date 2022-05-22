#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"
#include "quadtree.h"
#include "string"

std::vector<Block> creaWithFile(std::string namefile);
std::vector<Block> creaCharaWithFile(std::string namefile);
Quadtree leveltree(std::string namefile);
//void readColor(	char *file, double *r, double *g, double *b);
//void readColor(char *file, char c, double *r, double *g, double *b);

#endif