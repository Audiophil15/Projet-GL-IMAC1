#include "window.h"

Window::Window():baseW(80), baseH(40) ,scrW(900), scrH(450), ratio(80/40){};

Window::Window(int width, int height):baseW(80), baseH(40) ,scrW(width), scrH(height), ratio(80/40){};

Window::Window(int glwidth, int glheight, int width, int height):baseW(glwidth), baseH(glheight), scrW(width), scrH(height), ratio(((float)glwidth/glheight)){};


