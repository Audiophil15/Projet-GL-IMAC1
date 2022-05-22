#include "block.h"
#include <vector>
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
    //printf("size : %ld", tree->myblocks.size());
    //exit(0);
    //return myblocks;
    return tree->myblocks;
}

void Quadtree::insert(Block &b){
    if(this->isLeaf()){
        if(this->isFilled()){
            this->createChildren();
            for(Block block : myblocks){
                this->insert(block);
            }
            this->insert(b);
            myblocks.clear();
        }else{
            this->myblocks.push_back(b);
        }
    }else{
        insertInChildren(b);
    }

}

void Quadtree::render(Quadtree *tree){
    glColor3d(0,0,1);
    glBegin(GL_LINE_LOOP);
		glVertex2d(tree->xmin, tree->ymin);
		glVertex2d(tree->xmax-tree->xmin, tree->ymin);
		glVertex2d(tree->xmax-tree->xmin,  tree->ymax-tree->ymin);
		glVertex2d(tree->xmin, tree->ymax-tree->ymin);
	glEnd();

    if (!tree->isLeaf()){
    tree->render(tree->bl);
    tree->render(tree->tl);
    tree->render(tree->br);
    tree->render(tree->tr);
    }

}

void Quadtree::depth(){
    printf("depth call\n");
    /*glBegin(GL_LINE_LOOP);
		glVertex2d(this->xmin, this->ymin);
		glVertex2d(this->xmax-this->xmin, this->ymin);
		glVertex2d(this->xmax-this->xmin,  this->ymax-this->ymin);
		glVertex2d(this->xmin, this->ymax-this->ymin);
	glEnd();*/

    /*Block rect(this->xmin, this->ymin, this->xmax-this->xmin, this->ymax-this->ymin);
    rect.draw();*/
    if (!this->isLeaf()){
        this->bl->depth();
        this->br->depth();
        this->tl->depth();
        this->tr->depth();
    } else {
        /*Block rect(this->xmin, this->ymin, this->xmax-this->xmin, this->ymax-this->ymin);
        rect.draw();*/
        //rect.props();
        printf("la taille du tableau : %ld \n", myblocks.size());
        for (Block b:this->myblocks){
            printf("%.2lf : %.2lf\n", b.getPosX(), b.getPosY());
        }
    }
}


void Quadtree::createChildren(){
    this->tl = new Quadtree(this->xmin, this->ymax/2, this->xmax/2, this->ymax);
    this->bl = new Quadtree(this->xmin, this->ymin, this->xmax/2, this->ymax/2);
    this->tr = new Quadtree(this->xmax/2, this->ymax/2, this->xmax, this->ymax);
    this->br = new Quadtree(this->xmax/2, this->ymin, this->xmax, this->ymax/2);
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
    return (myblocks.size()>4);
}



void Quadtree::insertInChildren(Block &b){
    if(b.getCenterX()<(xmax+xmin)/2){
        //left
        insertLeft(b);

        if(b.getPosX()+b.getWidth()>(xmax+xmin)/2){
            //also right
            insertRight(b);
        }


    }else{
        //right
        insertRight(b);

        if(b.getPosX()<(xmax+xmin)/2){
            //also left
            insertLeft(b);
        }
    }
}

void Quadtree::insertRight(Block &b){
    if(b.getCenterY()<(ymax+ymin)/2){
        //in bottom right corner
        br->insert(b);

        if(b.getPosY()+b.getHeight()>(ymax+ymin)/2){
            //also in the top right corner
            tr->insert(b);
        }

    }else{
        //in top right corner
        tr->insert(b);

        if(b.getPosY()<(ymax+ymin)/2){
            //also in the bottom left corner
            br->insert(b);
        }

    }
}

void Quadtree::insertLeft(Block &b){
    if(b.getCenterY()<(ymax+ymin)/2){
        //in the bottom left corner
        bl->insert(b);

        if(b.getPosY()+b.getHeight()>(ymax+ymin)/2){
            //also in the top left corner
            tl->insert(b);
        }

    }else{
        //in the top left corner
        tl->insert(b);

        if(b.getPosY()<(ymax+ymin)/2){
            //also in the bottom left corner
            bl->insert(b);
        }
    }

}






