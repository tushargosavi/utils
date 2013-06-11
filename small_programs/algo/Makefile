OBJECTS=mergesort isprime multpoly bfs connectedcomp cc
CPPFLAGS=-g3 -O0 -I. -std=c++0x

all : $(OBJECTS)

bfs : graph.o gtraverse.o utils.o
connectedcomp : graph.o gtraverse.o utils.o
cc : graph.o gtraverse.o utils.o

clean:
	rm -f $(OBJECTS)
	rm -f *.o


