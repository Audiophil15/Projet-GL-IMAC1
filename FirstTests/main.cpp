#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>

#include "block.h"
#include "rectangle.h"
#include "window.h"
#include "graphics.h"

void axis();

int main(){

	Window win;

	//////
	initSDL();
	win.SDLWindow = initWindow(win.scrW, win.scrH);
	win.GLContext = contextInit(win.SDLWindow);
	windowResize(win.scrW, win.scrH, win);

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	int quit = 0;
	SDL_Event e;

	//////
	Rectangle* rectTab = (Rectangle*)malloc(sizeof(Rectangle)*25);
	Rectangle border(0,0,800,400);
	Block b(win.scrW/2, win.scrH/2, 25, 25, 0.3, 0.7, 0.2);

	for (int i = 0; i < 5; i++){
		for (int ii = 0; ii < 5; ii++){
			Rectangle r(i*50, ii*50+win.scrH-5*50, 50, 50, 1, 1-i/4., ii/4.);
			rectTab[i*5+ii] = r;
		}
	}

	//////
	int j,g;

	while(!quit){

		while(SDL_PollEvent(&e)){
			switch (e.type){
			case SDL_QUIT:
				quit = 1;
			break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED){
					windowResize(e.window.data1, e.window.data2, win);
				}
			case SDL_MOUSEMOTION:
				j = e.motion.x;
				g = e.motion.y;
			break;

			default:
			break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Drawings here

		// Border
		border.draw();

		// Carres colores
		for (int i = 0; i < 5; i++){
			for (int ii = 0; ii < 5; ii++){
				rectTab[i*5+ii].draw();
			}
		}

		// Devrait tracer les axes tous les 10 pixels, 80 fois pour aller jusqu'au bout des 800 pixels de large
		glPushMatrix();
		for (int i=0; i<80; i++){
			glLoadIdentity();
			glColor3f(0,i/79.,1-i/79.);
			glTranslatef(i*10,0,0);
			glBegin(GL_LINES);
				glVertex2f(0,0);
				glVertex2f(0,125);
			glEnd();
		}
		glPopMatrix();

		// Carre qui suit la souris
		int x = mapWindowToGLcoordinateX(j, win)-b.getWidth()/2;
		int y = mapWindowToGLcoordinateY(g, win)-b.getHeight()/2;
		b.moveto(x, y);
		b.setColor(0.5, x/win.baseW, y/win.baseH);
		b.draw();

		printf("Collisions : |");
		for (int i=0; i<25; i++){
			printf("%2d|", i);
		}
		printf("\n");
		printf("              ");
		for (int i=0; i<25; i++){
			if (b.collidesWith(rectTab[i])){
				printf(" #|");
			} else {
				printf("  |");
			}
		}
		printf("\n");
		printf("Mouse : %4d : %4d  ||  %f : %f  ", j, g, win.scrW, win.scrH);
		printf("||  %4d : %4d\n", mapWindowToGLcoordinateX(j, win), mapWindowToGLcoordinateY(g, win));
		SDL_GL_SwapWindow(win.SDLWindow);
	}

	SDL_GL_DeleteContext(win.GLContext);
	SDL_DestroyWindow(win.SDLWindow);
	SDL_Quit();

}

void axis(){
	// draw graduations
	glPushMatrix();
	glBegin(GL_LINES);
	for (int i = -45; i < 45; i++){
		glVertex2f(-.5,-i);
		glVertex2f(.5,-i);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = -45; i < 45; i++){
		glVertex2f(i,-0.5);
		glVertex2f(i,0.5);
	}
	glEnd();
	glPopMatrix();
}