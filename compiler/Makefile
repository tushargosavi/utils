OBJECTS=parser.o main.o keyword.o lexer.o node.o interpreter.o base_opr.o object.o 

GRAPH_OBJS=parser.o keyword.o lexer.o node.o show_graph.o main.o object.o


CFLAGS=-g3

in.exe : $(OBJECTS)
	gcc $(CFLAGS) -o in.exe $(OBJECTS)

lextest : lextest.o lexer.o
	gcc $(CFLAGS) -o lextest lextest.o lexer.o

lextest.o : lextest.c
	gcc $(CFLAGS) -o lextest.o -c lextest.c

lexer.o : lexer.c
	gcc $(CFLAGS) -o lexer.o -c lexer.c
	
lexer.c : lexer.l
	flex -o lexer.c lexer.l

keyword.o : keyword.c
	gcc $(CFLAGS) -o keyword.o -c keyword.c
	
parser.c : parser.y
	bison -o parser.c --defines parser.y

node.o : node.c
	gcc $(CFLAGS) -o node.o -c node.c

interpreter.o : interpreter.c
	gcc $(CFLAGS) -o interpreter.o -c interpreter.c

main.o : main.c
	gcc $(CFLAGS) -o main.o -c main.c	

graph:  $(GRAPH_OBJS)
	gcc $(CFLAGS) -o graph $(GRAPH_OBJS)

objtest : object.o base_opr.o objtest.o

clean :
	rm -f *.o
	rm -f test.exe in.exe graph
	rm -f parser.c parser.h lexer.c lex.yy.c
