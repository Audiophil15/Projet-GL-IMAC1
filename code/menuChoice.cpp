#include <GL/gl.h>

#include "menuChoice.h"

#include "rectangle.h"

Choice::Choice():rectangle({0.,0.,0.,0.}){}

Choice::Choice(Rectangle rect):rectangle(rect){}

Choice::Choice(Rectangle rect, GLuint txtBack):rectangle(rect), textureBack(txtBack){}

Choice::Choice(Rectangle rect, GLuint txtBack, GLuint txtFront):rectangle(rect), textureBack(txtBack), textureFront(txtFront){}

