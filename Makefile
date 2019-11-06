CC = gcc
C++ = g++
OPT = -O4

all: strassen

clean: 
	@rm *.x 

strassen: strassen/strassen.c utility.c strassen/main.c strassen/hw.c
		$(CC) $(OPT) strassen/hw.c strassen/main.c strassen/strassen.c utility.c -o strassen.x   

chain: utility.c chain_mult/chain_mm.c chain_mult/main.c
		$(CC) $(OPT) chain_mult/chain_mm.c chain_mult/main.c utility.c -o chain.x

sorting: utility.c sorting/sorting.c sorting/vector.c sorting/main.c 
		$(CC) $(OPT) utility.c sorting/sorting.c sorting/vector.c sorting/main.c -o sorting.x

heap: utility.c heap/heap.c heap/main.c 
		$(CC) $(OPT) utility.c heap/heap.c heap/main.c -o heap.x

.PHONY: all clean