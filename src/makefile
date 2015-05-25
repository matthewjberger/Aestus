## Files to compile
OBJS = *.cpp

# Executable name
OBJ_NAME = vimTest

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS=$(shell sdl2-config --cflags)

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS=$(shell sdl2-config --libs)

# Compiler being used
CC = g++ -std=c++11

# Compiler flags
COMPILER_FLAGS = -w

# Linker flags
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Target
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
