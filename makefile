### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall -g
OBJ= distancias.o filemanager.o main.o knn.o
EXEC= distancias filemanager knn

all: main
	-rm *.o
	-rm *.txt

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
	-rm *.o
	-rm distancias
	-rm filemanager
	-rm knn
	-rm main

run:
	$ make
	$ ./main ${ARG}

val: main
	$ valgrind ./main ${ARG}