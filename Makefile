CC=gcc
CFLAGS=-g -Wall -ansi -pedantic -O3

wordmorph: main.o matriz.o ordenacao.o ficheiros.o lista.o functional.o heap.o
	$(CC) $(CFLAGS) -o wordmorph main.o matriz.o ordenacao.o ficheiros.o lista.o functional.o heap.o

main.o: main.c matriz.h ordenacao.h ficheiros.h lista.h functional.h heap.h
	$(CC) -c $(CFLAGS) main.c

matriz.o: matriz.c matriz.h ficheiros.h
	$(CC) -c $(CFLAGS) matriz.c

ordenacao.o: ordenacao.c ordenacao.h 
	$(CC) -c $(CFLAGS) ordenacao.c

ficheiros.o: ficheiros.c ficheiros.h
	$(CC) -c $(CFLAGS) ficheiros.c

functional.o: functional.c functional.h matriz.h lista.h heap.h
	$(CC) -c $(CFLAGS) functional.c

lista.o: lista.c lista.h
	$(CC) -c $(CFLAGS) lista.c

heap.o: heap.c heap.h
	$(CC) -c $(CFLAGS) heap.c

clean::
	rm -f *.o core a.out wordmorph *~
