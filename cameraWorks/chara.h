#ifndef CHARA_H
#define CHARA_H

#include <SDL2/SDL.h>

class Chara {
	public :
        int numberChara;
        int selectedChara = 0; 
        int previousChara = numberChara-1;

		Chara();
        Chara(int nbChara);
        Chara(int nbChara, int slChara);
};

#endif