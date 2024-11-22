# Variables for Compiler
CC = gcc
CFLAGS = -g -Wall --pedantic
LD_FLAGS = -L/usr/local/lib -lSDL3

# Variables for program
executable = sdl3
source = sdl3.c

# Default (First) Target
${executable}: ${source}
	${CC} ${CFLAGS} ${source} -o ${executable} ${LD_FLAGS}

# Commonly used target for cleaning up targets
clean:
	rm ${executable}