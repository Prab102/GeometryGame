#to build assignment :
#	cd assignment dir
#    make
#exe binaries should be put in dir/bin, to run you then need to cd into bin and type ./outputfile

#DEFINE compiler to use
CXX		:= g++
OUTPUT  := sfmlgame

#if need to specify sfml install directory
SFML_DIR := /opt/homebrew/Cellar/sfml/2.6.1/


#compiler and linker flags 0 or O
CXX_FLAGS	:= -O3 -std=c++17
INCLUDES	:= -I ./src -I$(SFML_DIR)/include
LDFLAGS		:= -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFML_DIR)/lib

#srcfiles for ecs game engine

SRC_FILES	:= $(wildcard src/*.cpp)
OBJ_FILES	:= $(SRC_FILES:.cpp=.o)

#all of these targets will be made if you just type make
all:$(OUTPUT)

#define the main executable requirments
$(OUTPUT):$(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

#specifies how the object files are compiled from cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

#typing 'make clean' will remove all intermediate build files

clean:
	rm -f $(OBJ_SFMLGAME) ./bin/sfmlgame

# typing make run will compile and run the program
run: $(OUTPUT)
	cd bin && ./sfmlgame && cd ..