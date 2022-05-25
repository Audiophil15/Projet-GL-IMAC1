#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "portail.h"

Portail::Portail(double x, double y, double w, double h, double r, double g, double b):Rectangle{x,y,w,h,r,g,b}{}

int Portail::isExit(Block character){
    return (this->getWidth()==character.getWidth() && this->getHeight()==character.getHeight());
}


