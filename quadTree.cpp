#include "block.h"
#include <vector>
#include "quadtree.h"

using namespace std;

Quadtree::Quadtree():Quadtree(0,0,0,0){}
Quadtree::Quadtree(int xmin, int ymin, int xmax, int ymax):xmin(xmin), ymin(ymin), xmax(xmax), ymax(ymax){}


void Quadtree::insert(Block &b){
    if(this->isLeaf()){
        if(this->isFilled()){
            this->createChildren();
            for(Block block : myblocks){
                this->insert(block);                     
            }
            myblocks.clear();
        }else{
            this->myblocks.push_back(b);
        }
    }else{
        insertInChildren(b);
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
    return (myblocks.size()>10);
}



void Quadtree::insertInChildren(Block &b){
    if(b.getCenterX()<xmax/2){
        //left
        insertLeft(b);

        if(b.getPosX()+b.getWidth()>xmax/2){
            //also right
            insertRight(b);
        }


    }else{
        //right
        insertRight(b);

        if(b.getPosX()<xmax/2){
            //also left 
            insertLeft(b);
        }
    }
}

void Quadtree::insertRight(Block &b){
    if(b.getCenterY()<ymax/2){
        //in bottom right corner
        br->insert(b);

        if(b.getPosY()+b.getHeight()>ymax/2){
            //also in the top right corner
            tr->insert(b);
        }
        
    }else{
        //in top right corner
        tr->insert(b);

        if(b.getPosY()<ymax/2){
            //also in the bottom left corner
            br->insert(b);  
        }

    }
}

void Quadtree::insertLeft(Block &b){
    if(b.getCenterY()<ymax/2){
        //in the bottom left corner
        bl->insert(b);

        if(b.getPosY()+b.getHeight()>ymax/2){
            //also in the top left corner
            tl->insert(b);
        }

    }else{
        //in the top left corner
        tl->insert(b);

        if(b.getPosY()<ymax/2){
            //also in the bottom left corner  
            bl->insert(b);
        }
    }

}

    




