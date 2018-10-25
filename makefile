### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall

all: main
	$ rm *.o
	$ mv main programa
	$ ./programa

main: main.o distancias.o
	$ gcc -o main main.o distancias.o -lm

main.o: main.c
	$ gcc -c main.c

distancias.o: distancias.c
	$ gcc -c distancias.c