CC = g++
SRCPATH = code
OBJPATH = objects
HEADERS = headers
CXXFLAGS = -g -MMD -Iheaders
LIBFLAGS = -lSDL2 -lGL -lGLU -lm -lSDL2_image -lSDL2_mixer
SOURCES = $(filter-out $(SRCPATH)/main.cpp $(SRCPATH)/treetest.cpp, $(wildcard $(SRCPATH)/*.cpp))
OBJ = ${subst $(SRCPATH),$(OBJPATH),$(SOURCES:.cpp=.o)}
DEPENDS = $(SOURCES:.cpp=.d)

main : $(OBJPATH)/main.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

$(OBJPATH)/main.o : $(SRCPATH)/main.cpp
	mkdir -p $(OBJPATH)
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS) -o $@

treetest : treetest.o $(OBJ)
	$(CC) $^ -o $@ $(CXXFLAGS) $(LIBFLAGS)

$(OBJPATH)/%.o : $(SRCPATH)/%.cpp $(HEADERS)/%.h
	mkdir -p $(OBJPATH)
	$(CC) $< -c $(CXXFLAGS) $(LIBFLAGS) -o $@

-include $(DEPENDS)

clean :
	rm $(OBJPATH)/*
