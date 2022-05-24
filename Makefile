CC = g++
CXXFLAGS = -g -MMD
LIBFLAGS = -lSDL2 -lGL -lGLU -lm -lSDL2_image
SOURCES = $(filter-out main.cpp treetest.cpp, $(wildcard *.cpp))
OBJ = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)

main : main.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

main.o : main.cpp
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS)

treetest : treetest.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

%.o : %.cpp %.h
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS)

-include $(DEPENDS)

clean :
	rm -rf $(OBJ)
	rm -rf $(DEPENDS)