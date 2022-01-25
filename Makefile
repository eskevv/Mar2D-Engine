#SOURCE FILES
SOURCE := src/Game/*.cpp
SOURCE += src/Engine/*.cpp


#INCLUDE PATHS
INCLUDES := -ID:/Dev/Libraries/include
INCLUDES += -Isrc/Game
INCLUDES += -Isrc/Engine

#LIBRARY PATHS
LIBPATHS := -LD:/Dev/Libraries/lib
LIBPATHS += -LD:/Dev/Libraries/SDL2/lib

#LINKER FLAGS
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua54

#COMPILER FLAGS
FLAGS := -Wall -Wfatal-errors -std=c++17

#PROGRAM
FILE := engine

#OUTPUT
OBJ_NAME := bin/$(FILE)


build:
	g++ $(FLAGS) $(SOURCE) $(INCLUDES) $(LIBPATHS) $(LIBS) -o $(OBJ_NAME)

run:
	cls && cd bin && $(FILE)

clean:
	del $(OBJ_NAME)