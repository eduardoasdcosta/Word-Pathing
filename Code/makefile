CC = gcc
CFLAGS = -Wall -ansi

SOURCES = main.c file.c list.c graph.c heap.c

OBJECTS = main.o file.o list.o graph.o heap.o

wordmorph: $(OBJECTS)
	gcc -O2 -o $@ $(OBJECTS)

clean::
	rm -f *.o core a.out wordmorph *~


