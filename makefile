### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall -g

all: main
	$ rm *.o

main: main.o distancias.o openfile.o
	$ ${CC} -o main main.o distancias.o openfile.o -lm ${CFLAGS}

main.o: main.c
	$ ${CC} -c main.c ${CFLAGS}

distancias.o: distancias.c
	$ ${CC} -c distancias.c ${CFLAGS}

openfile.o: openfile.c
	$ ${CC} -c openfile.c ${CFLAGS}

clean:
	$ rm *.o

run: main
	$./main

val: main
	$(valgrind ./main)