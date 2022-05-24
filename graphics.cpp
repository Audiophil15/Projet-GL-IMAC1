#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>

#include "graphics.h"
#include "window.h"
#include "menu.h"

void initSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error initializing : %s\n", SDL_GetError());
		exit(11);
	}
}

SDL_Window* initWindow(int width, int height){
	SDL_Window* w;

	w = SDL_CreateWindow("Rectangle and Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (w==NULL){
		printf("Error creating window : %s\n", SDL_GetError());
		exit(12);
	}
	return w;
}

SDL_GLContext contextInit(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if(context == NULL){
		printf("Error creating OpenGL context : %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(16);
	}

	return context;

}

int mapWindowToGLcoordinateX(int windowCoord, Window w){
	int shift;
	float ratio;
	if (w.scrW/w.scrH > w.ratio){
		shift = (w.scrW-w.scrH*w.ratio)/2;
		ratio = w.baseH/w.scrH;
	} else {
		shift = 0;
		ratio = w.baseW/w.scrW;
	}

	return (windowCoord - shift)*ratio;
}

int mapWindowToGLcoordinateY(int windowCoord, Window w){
	int shift;
	float ratio;
	if (w.scrW/w.scrH < w.ratio){
		shift = (w.scrH-w.scrW/w.ratio)/2;
		ratio = w.baseW/w.scrW;
	} else {
		shift = 0;
		ratio = w.baseH/w.scrH;
	}

	return (w.scrH - windowCoord - shift)*ratio;
}

void windowResize(int newWidth, int newHeight, Window& win){
	win.scrW = (float)newWidth;
	win.scrH = (float)newHeight;
	onWindowResized(win);
}

void onWindowResized(Window w){
	// printf("Window resized : %4d, %-4d\n", w.scrW, w.scrH);
	// If screen is wider than original window
	if(w.scrW/(float)w.scrH > w.ratio){
		glViewport(0+(w.scrW-w.scrH*w.ratio)/2, 0, w.scrH*w.ratio, w.scrH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	} else {
		glViewport(0,0+(w.scrH-w.scrW/w.ratio)/2, w.scrW, w.scrW/w.ratio);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}
	gluOrtho2D(
	0, w.baseW*w.zoom,
	0, w.baseH*w.zoom);
}


GLuint initializeTexure(std::string chemin){

	SDL_Surface* img= IMG_Load(chemin.c_str());
	if(img==NULL){
		exit(-1);
	}


	GLuint texture;


	glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);


	return texture;
}


void textureBackground(GLuint texture, Window win){
	//texture
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);


		glBegin(GL_QUADS);
			glColor3f(1,1,1);

			glTexCoord2f(0,1);
            glVertex2f(0,0);

			glTexCoord2f(1,1);
            glVertex2f(win.baseW, 0);

			glTexCoord2f(1,0);
            glVertex2f(win.baseW, win.baseH);

			glTexCoord2f(0,0);
            glVertex2f(0, win.baseH);

        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
}


void textureMenu(Choice texture){
	//texture
        glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture.textureBack);

		double left = texture.rectangle.getPosX();
		double right = texture.rectangle.getPosX() + texture.rectangle.getWidth();
		double bottom = texture.rectangle.getPosY();
		double top = texture.rectangle.getPosY()+texture.rectangle.getHeight();



		glBegin(GL_QUADS);
			glColor3f(1,1,1);

			glTexCoord2f(0,1);
            glVertex2f(left,bottom);

			glTexCoord2f(1,1);
            glVertex2f(right, bottom);

			glTexCoord2f(1,0);
            glVertex2f(right, top);

			glTexCoord2f(0,0);
            glVertex2f(left, top);

        glEnd();


        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
}

void textureMenuTop(Choice texture){
	//texture
        glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture.textureFront);

		double left = texture.rectangle.getPosX();
		double right = texture.rectangle.getPosX() + texture.rectangle.getWidth();
		double bottom = texture.rectangle.getPosY();
		double top = texture.rectangle.getPosY()+texture.rectangle.getHeight();



		glBegin(GL_QUADS);
			glColor3f(1,1,1);

			glTexCoord2f(0,1);
            glVertex2f(left,bottom);

			glTexCoord2f(1,1);
            glVertex2f(right, bottom);

			glTexCoord2f(1,0);
            glVertex2f(right, top);

			glTexCoord2f(0,0);
            glVertex2f(left, top);

        glEnd();


        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
}

void deleteTexture(GLuint *texture){
    glDeleteTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, 0);
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
