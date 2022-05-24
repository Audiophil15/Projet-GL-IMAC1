#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include "color.h"
#include "block.h"
#include "rectangle.h"
#include "window.h"
#include "graphics.h"
#include "chara.h"
#include "level.h"
#include "quadtree.h"

void axis(int baseW, int baseH);

int main(){

	Window win;
	win.zoom = getZoom("levels/level4");
	Chara chara(3);
	initSDL();
	win.SDLWindow = initWindow(win.scrW, win.scrH);
	win.GLContext = contextInit(win.SDLWindow);
	windowResize(win.scrW, win.scrH, win);

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	int quit = 0;
	SDL_Event e;

	int numberChara = 3;

	Block* charaTab = (Block*)malloc(sizeof(Block)*chara.numberChara);

	//

	//Block perso1((int)win.scrW/2, (int)win.scrH/2, 1, 5, 0.025, 0., -58.8, 0.921, 0.376, 0.376); 
	//Block perso1(2, win.baseH, 1, 2, 0.025, 0., -58.8, 0.921, 0.376, 0.376); //lvl1

	//Block perso1(2, win.baseH, 1, 1, 0.025, 0., -58.8, 0.921, 0.376, 0.376); //lvl4
	//Block perso1(2, 22, 1, 1, 0.025, 0., -58.8, 0.921, 0.376, 0.376);
	//Block perso1(10, 33, 1, 2, 0.025, 0., -58.8, 0.921, 0.376, 0.376); //lvl 3
	//Block perso2((int)win.scrW/2 - 100, (int)win.scrH/2, 15, 15, 1, 0., -9.8, 0.937, 0.933, 0.560);
	Block perso3((int)win.scrW/2 + 100, (int)win.scrH/2, 30, 30, 1, 0., -9.8, 0.937, 0.560, 0.870);

	//Block plateforme(0, 0, win.baseW, win.baseH/5);
	/*Block b1(0, win.baseH/5, 5, 5, 0.2, 0.5, 0.1);
	Block b2(win.baseW-50, win.baseH/5, 5, 5, 0.1, 0.5, 0.3);*/


	//std::vector<Block>myblocks = creaWithFile("levels/level1");
	std::vector<Block>myblocks = creaWithFile("levels/level4");
	std::vector<Block>charas = creaCharaWithFile("levels/level4");
	std::vector<Block> env;
	//Quadtree quad = leveltree("levels/level4");

	//Quadtree quad(-80,0,184, 72);
	//Quadtree quad(-40,0,92, 36); //lvl4
	//Quadtree quad(-40,0,94, 40); //lvl3
	//Quadtree quad(-40,0,285, 140);  //lvl2
	//Quadtree quad(0,0,148, 80); //lvl1
	//Quadtree quad(0,0,40,40);

	//quad.initialize(myblocks);
	//quad.initialize(tab);
	/**/
	//quad.depth();
	
	//env.push_back(plateforme);
	/*env.push_back(b1);
	env.push_back(b2);*/

	for (int i = 0; i < myblocks.size(); i++){
		env.push_back(myblocks.at(i));
	}
	

	//charaTab[0] = perso1;
	charaTab[0] = charas[0];
	//charaTab[1] = perso2;
	charaTab[1] = charas[1];
	//charaTab[2] = perso3;
	charaTab[2] = charas[2];

	Block selectedBlock = charaTab[chara.selectedChara];

	double camx = 0;
	double camy = 0;

	double dt = 1.0/60;
	int accelFactor = 50;


	while(!quit){

		//myblocks=quad.myblocks;
		//quad.depth();
		//myblocks = quad.findChild(&quad, selectedBlock.getPosX(), selectedBlock.getPosY());

		//myblocks = quad.findChild(&quad, 5, 26);
		/*for (Block b : myblocks){
			printf("%lf", b.getPosX());
		}*/

		while(SDL_PollEvent(&e)){
			switch (e.type){
			case SDL_QUIT:
				quit = 1;
			break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED){
					windowResize(e.window.data1, e.window.data2, win);
				}
			break;
			case SDL_KEYDOWN :
				switch(e.key.keysym.sym){
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = 1;
					break;

					case SDLK_TAB :

						if(chara.selectedChara <2){
							chara.selectedChara+=1;
						}else {
							chara.selectedChara=0;
						}

						if(chara.selectedChara> 0){
							chara.previousChara= chara.selectedChara - 1;
						}else{
							chara.previousChara =2;
						}

						selectedBlock = charaTab[chara.selectedChara];

					break;


					case SDLK_UP:
						selectedBlock.jump();
					break;

				}
			break;

			default:
			break;
			}
		}

	

		selectedBlock.isMovingLeft = (int)keystate[SDL_SCANCODE_LEFT];
		selectedBlock.isMovingRight = (int)keystate[SDL_SCANCODE_RIGHT];

		// Updates physics variables

		//selectedBlock.updatePosition(myblocks, dt);
		selectedBlock.updatePosition(env, dt);



		// charaTab[chara.previousChara].updatePosition(env, dt);
		// .speed.y += dt*charaTab[chara.previousChara].acc.y * accelFactor;
		// charaTab[chara.previousChara].position.y += dt*charaTab[chara.previousChara].speed.y;

		// if (charaTab[chara.previousChara].position.y<plateforme.position.y){
		// 	charaTab[chara.previousChara].position.y -= dt*charaTab[chara.previousChara].speed.y;
		// 	charaTab[chara.previousChara].speed.y = 0;
		// }

		camx = selectedBlock.getPosX();
		camy = selectedBlock.getPosY();
		camx = std::max(0., camx-win.baseW*win.zoom/2);
		//camx = std::max(0., camx-win.baseW/2);
		// camx = min(camx, map.getWidth());
		camy = std::max(0., camy-win.baseH*win.zoom/5);

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		// camera

		glColor3f(1,0,0);
		//axis(win.baseW, win.baseH);
		

		glPushMatrix();



			//glTranslatef(-camx + win.baseW/2, -camy + win.baseH/5, 0);
			glTranslatef(-camx, -camy, 0);
			glColor3f(0,1,0);
			//axis(win.baseW, win.baseH);

			/*for (int i = 0; i < myblocks.size(); i++){
				myblocks.at(i).draw();
			}*/
			
			selectedBlock.draw();
			for (Block b : env){
				b.draw();
			}
			//quad.render(&quad);
			// for(int i=0; i< numberChara; i++){
			// 	charaTab[i].draw();
			// }

		glPopMatrix();



		SDL_GL_SwapWindow(win.SDLWindow);
	}

	SDL_GL_DeleteContext(win.GLContext);
	SDL_DestroyWindow(win.SDLWindow);
	SDL_Quit();

}


void axis(int baseW, int baseH){
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(baseW/2 - 30, baseH/2);
		glVertex2f(baseW/2 + 30, baseH/2);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(baseW/2, baseH/2 - 30);
		glVertex2f(baseW/2, baseH/2 + 30);

	glEnd();
	glPopMatrix();
}






