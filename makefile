### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall -g
OBJ= distancias.o filemanager.o knn.o main.o
EXEC= distancias filemanager knn

all: main
	$ rm *.o

main: ${OBJ}
	$ ${CC} -o main ${OBJ} -lm ${CFLAGS}

main.o: main.c
	$ ${CC} -c main.c ${CFLAGS}

distancias.o: distancias.c
	$ ${CC} -c distancias.c ${CFLAGS}

filemanager.o: filemanager.c
	$ ${CC} -c filemanager.c ${CFLAGS}

knn.o: knn.c
	$ ${CC} -c knn.c ${CFLAGS}

clean:
	$ rm main
	$ rm *.o

run: main
	$ rm *.o
	$ ./main

val: main
	$ valgrind ./main