#Author: Karl Abrahamson
CFLAGS = -g -Wall -Wshadow -Wuninitialized
CC     = g++
LINK   = g++
OFILESH = huffman.o trace.o binary2.o pqueue.o
OFILESU = unhuffman.o trace.o binary2.o
OFILES  = huffman.o unhuffman.o trace.o binary2.o pqueue.o

runh: huffman
	./huffman

debugh: huffman
	gdb ./huffman

runu: unhuffman
	./unhuffman

debugu: unhuffman
	gdb ./unhuffman

huffman : $(OFILESH)
	$(LINK) -o huffman $(OFILESH) 

unhuffman : $(OFILESU)
	$(LINK) -o unhuffman $(OFILESU) 

huffman.o: huffman.cpp trace.h binary.h
	$(CC) $(CFLAGS) -c huffman.cpp

unhuffman.o: unhuffman.cpp trace.h binary.h
	$(CC) $(CFLAGS) -c unhuffman.cpp

trace.o: trace.cpp trace.h
	$(CC) $(CFLAGS) -c trace.cpp

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

binary2.o: binary2.cpp
	$(CC) $(CFLAGS) -c binary2.cpp

clean: 
	rm $(OFILES) huffman unhuffman
