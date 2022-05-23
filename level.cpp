#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <vector>

#include "level.h"
#include "block.h"
#include "chara.h"
//#include "quadtree.h"
#include "string"


std::vector<Block> creaWithFile(std::string namefile){
	std::vector<Block> myblocks;

	FILE* file = fopen(namefile.c_str() , "r");
	char p;
	double r=1;
	double g=1;
	double b=1;
	int v, d1, d2, d3, d4;
	double zoom = 1;
	char *parameter = (char *) malloc( 10 * sizeof(char));

	char *file_contents = (char *) malloc( 50 * sizeof(char));

	char *test = (char *) malloc( 10 * sizeof(char));

	do{
		fscanf(file, "%[^\n] ", file_contents);
		char * copy = (char *) malloc(strlen(file_contents) + 1); 
		strcpy(copy, file_contents);
		parameter = strtok(copy, " ");
		printf("%s", file_contents);


		switch(parameter[0]){
			case 'c' :
				sscanf(file_contents, "%*s %lf %lf %lf", &r, &g, &b);
			break;
			
			case 'z' :
				sscanf(file_contents, "%*s %lf", &zoom);
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	do {
	v = 0;
	v += fscanf(file, "%d", &d1);
	v += fscanf(file, "%d", &d2);
	v += fscanf(file, "%d", &d3);
	v += fscanf(file, "%d", &d4);
	if (v == 4){
		Block blocks(d1*zoom, d2*zoom, d3*zoom, d4*zoom,r,g,b);
		//myblocks[i++] = rect;
		myblocks.push_back(blocks);
		}
	}
	while (v == 4); 

	return myblocks;

}


std::vector<Block> creaCharaWithFile(std::string namefile){
	std::vector<Block> charas;

	FILE* file = fopen(namefile.c_str() , "r");
	char p;
	double r=1;
	double g=1;
	double b=1;
	double x=0;
	double y=0;
	double sizeX = 1;
	double sizeY = 1;
	char *parameter = (char *) malloc( 10 * sizeof(char));
	char *file_contents = (char *) malloc( 50 * sizeof(char));


	do{
		fscanf(file, "%[^\n] ", file_contents);
		char * copy = (char *) malloc(strlen(file_contents) + 1); 
		strcpy(copy, file_contents);
		parameter = strtok(copy, " ");
		printf("%s", file_contents);

		switch(parameter[0]){
			case 'r' : { 

				sscanf(file_contents, "%*s %lf %lf %lf %lf %lf %lf %lf", &x, &y, &sizeX, &sizeY, &r, &g, &b);
				//Block chara(x, y, sizeX, sizeY, 0.025,r,g,b, 0.376, 0.376);
				Block chara(x, y, sizeX, sizeY, 0.025, 0., -58.8, r,g,b);
				charas.push_back(chara);
			}
			break;

			default:
			break;
		}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));


	return charas;

}

Quadtree leveltree(std::string namefile){
	int xmin=0;
	int ymin=0;
	int xmax=0;
	int ymax=0;
	FILE* file = fopen(namefile.c_str() , "r");
	char *parameter = (char *) malloc( 10 * sizeof(char));
	char *file_contents = (char *) malloc( 50 * sizeof(char));

	do{
	fscanf(file, "%[^\n] ", file_contents);
	char * copy = (char *) malloc(strlen(file_contents) + 1); 
	strcpy(copy, file_contents);
	parameter = strtok(copy, " ");
	printf("%s", file_contents);

	switch(parameter[0]){
			case 'q' : { 

				sscanf(file_contents, "%*s %d %d %d %d", &xmin, &ymin, &xmax, &ymax);
			}
			break;

			default:
			break;
	}

	} while ( (parameter[0]>='a' && parameter[0]<='z') || (parameter[0]>='A' && parameter[0]<='Z'));

	//Quadtree tree(xmin*zoom, ymin*zoom, xmax*zoom, ymax*zoom);
	Quadtree tree(xmin, ymin, xmax, ymax);
	return tree;
}