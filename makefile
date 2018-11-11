### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS=-Wall -g
OBJ= src/distancias.o src/filemanager.o src/knn.o main.o
EXEC= distancias filemanager knn

all: main
	-rm ${OBJ}

main: ${OBJ}
	$ ${CC} -o main ${OBJ} -lm ${CFLAGS}

main.o: main.c
	$ ${CC} -c main.c ${CFLAGS}

distancias.o: distancias.c
	$ ${CC} -c src/distancias.c ${CFLAGS}

filemanager.o: filemanager.c
	$ ${CC} -c src/filemanager.c ${CFLAGS}

knn.o: knn.c
	$ ${CC} -c src/knn.c ${CFLAGS}

clean:
	-rm ${OBJ}
	-rm ${EXEC}

run:
	$ make
	$ ./main ${ARG}

val: main
	$ valgrind -v --leak-check=full ./main ${ARG}