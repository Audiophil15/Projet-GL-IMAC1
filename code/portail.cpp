#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "portail.h"

Portail::Portail(double x, double y, double w, double h, double r, double g, double b):Rectangle{x,y,w,h,r,g,b},foundChara(0){}

int Portail::isExit(Block* character){
    return (this->getWidth()==character->getWidth() && this->getHeight()==character->getHeight());
}

void Portail::isFound(){
    this->foundChara = 1;
}

void Portail::isNotFound(){
    this->foundChara = 0;
}

int Portail::getFound(){
    return this->foundChara;
}
