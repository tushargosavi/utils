CPPFLAGS= -fexceptions --std=c++11
LIBS=-pthread -lboost_system -lboost_filesystem -lboost_thread-mt -lpthread
CC=g++

.PHONY: dep clean all

all : pio

dep : makefile.dep
makefile.dep : *.cpp *.h
	for file in *.cpp; do gcc -MM $(CPPFLAGS) "$${file}"; done > $@

include makefile.dep

pio : pio.o

clean:
	rm -f *.o pio makefile.dep
