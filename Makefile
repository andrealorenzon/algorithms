CC = gcc
C++ = g++
OPT = -O4

all: strassen

clean: 
	@rm *.x

strassen: strassen/strassen.c utility.c strassen/main.c
		$(CC) $(OPT) strassen/main.c strassen/strassen.c utility.c -o strassen.x   

.PHONY: all clean