### Makefile ###
# diz que o programa é em C e deve usar o GCC
CC=gcc
# liga algumas flags de warn, mas não todas
CFLAGS= -g -Wall -O2 -w
OBJ= src/distancias.o src/filemanager.o src/knn.o src/aux.o trab1.o
EXEC= distancias filemanager knn aux
PREDIC= data/iris/predicoes/* data/vowels/predicoes/*

all: trab1
	-rm ${OBJ}

trab1: ${OBJ}
	$ ${CC} -o trab1 ${OBJ} -lm ${CFLAGS}

trab1.o: trab1.c
	$ ${CC} -c trab1.c ${CFLAGS}

distancias.o: distancias.c
	$ ${CC} -c src/distancias.c ${CFLAGS}

filemanager.o: filemanager.c
	$ ${CC} -c src/filemanager.c ${CFLAGS}

knn.o: knn.c
	$ ${CC} -c src/knn.c ${CFLAGS}

aux.o: aux.c
	$ ${CC} -c src/aux.c ${CFLAGS}

clean:
	-rm ${OBJ}
	-rm ${EXEC}
	-rm ${PREDIC}
	#-rm main
	-rm trab1
	
run: all
	$ time ./trab1

val: trab1
	$ valgrind --leak-check=full ./trab1
	-rm ${OBJ}
