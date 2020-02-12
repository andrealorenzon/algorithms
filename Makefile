CC = gcc
C++ = g++
OPT = -O4

all: strassen

clean: 
	@rm *.x*

strassen: strassen/strassen.c utility.c strassen/main.c strassen/hw.c
		$(CC) $(OPT) strassen/hw.c strassen/main.c strassen/strassen.c utility.c -o strassen.x   

chain: chain_mult/chain_mm.c chain_mult/main.c chain_mult/matrix.c
		$(CC) $(OPT) chain_mult/chain_mm.c chain_mult/matrix.c chain_mult/main.c -o chain.x

chain_my: chain_mult/my_cmm.c
		$(CC) $(OPT) chain_mult/my_cmm.c -o chain.x

sorting: utility.c sorting/sorting.c sorting/vector.c sorting/main.c heap/heap.h
		$(CC) $(OPT) utility.c sorting/sorting.c sorting/vector.c sorting/main.c heap/heap.c -o sorting.x

heap: utility.c heap/heap.c heap/main.c 
		$(CC) $(OPT) utility.c heap/heap.c heap/main.c -o heap.x

#dijkstraV: dijkstra/dijkstraVector.cpp
#		$(C++) $(OPT) dijkstra/dijkstraVector.cpp -o main1.xpp

dijkstra2: dijkstra/utility.cpp dijkstra/main.cpp
		$(C++) $(OPT) dijkstra/utility.cpp dijkstra/main.cpp -o main2.x

dijkstraHeap: dijkstraHeap/main.cpp 
		$(C++) $(OPT) dijkstraHeap/main.cpp  -o mainH.x

dijkstraOld: dijkstraHeap/mainOld.cpp 
		$(C++) $(OPT) dijkstraHeap/mainOld.cpp  -o mainOld.x

.PHONY: all clean