CC = gcc
C++ = g++
OPT = -O4

all: strassen

clean: 
	@rm *.x 

strassen: strassen/strassen.c utility.c strassen/main.c strassen/hw.c
		$(CC) $(OPT) strassen/hw.c strassen/main.c strassen/strassen.c utility.c -o strassen.x   

.PHONY: all clean