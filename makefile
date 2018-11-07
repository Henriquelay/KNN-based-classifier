### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall -g
OBJ= distancias.o openfile.o main.o
EXEC= distancias openfile

all: main
	$ rm *.o

main: ${OBJ}
	$ ${CC} -o main ${OBJ} -lm ${CFLAGS}

main.o: main.c
	$ ${CC} -c main.c ${CFLAGS}

distancias.o: distancias.c
	$ ${CC} -c distancias.c ${CFLAGS}

openfile.o: openfile.c
	$ ${CC} -c openfile.c ${CFLAGS}

clean:
	$ rm main

run: main
	$ ./main

val: main
	$ valgrind ./main