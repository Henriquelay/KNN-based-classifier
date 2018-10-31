### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall

all: programa
	$ rm *.o
# $ mv programa main
# $ ./main

programa: main.o distancias.o
	$ gcc -o programa main.o distancias.o -lm

main.o: main.c
	$ gcc -c main.c

distancias.o: distancias.c
	$ gcc -c distancias.c

clean:
	$ rm *.o
	$ rm programa