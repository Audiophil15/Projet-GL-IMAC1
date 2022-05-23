CC = g++
CXXFLAGS = -g -MMD
LIBFLAGS = -lSDL2 -lGL -lGLU -lm -lSDL2_image
SOURCES = $(filter-out treetest.cpp, $(wildcard *.cpp))
OBJ = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

main : $(OBJ)
	$(CC) $(OBJ) -o $@ $(CXXFLAGS) $(LIBFLAGS)

main.o : main.cpp
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS)

treetest : treetest.o block.o quadtree.o graphics.o window.o rectangle.o
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

%.o : %.cpp %.h
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS)

-include $(DEPENDS)

clean :
	rm -rf $(OBJ)
	rm -rf $(DEPENDS)