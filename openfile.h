/* HEADER PARA A BIBLIOTECA OPENFILE */
#ifndef _H_OPENFILE
#define _H_OPENFILE
/*Aqui vai as funcoes*/
#include <stdio.h>

typedef struct Tpaths Tpaths;
typedef struct Tamostra Tamostra;

Tpaths* novoPaths(char*, char*, char*);
char* returnPath(Tpaths, int);
Tamostra* novaAmostra(int, char, float);
void printerAmostras(Tamostras*);
void textSize(FILE*, int*, int*);
void printaMatriz(float**, float*, int, int);
void transcribe(FILE*, float**, float*, int, int);
int countLinhas(FILE*);
int countChars(FILE*, int);
void tiraQuebra(char*);
Tpaths* setupPaths(FILE*);
void setupAmostra(FILE*, int, Tamostra**);

/*Endif para evitar warnings*/
#endif