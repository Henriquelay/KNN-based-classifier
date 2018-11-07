/* HEADER PARA A BIBLIOTECA OPENFILE */
#ifndef _H_OPENFILE
#define _H_OPENFILE
/*Aqui vai as funcoes*/
#include <stdio.h>

void textSize(FILE*, int*, int*);
void printaMatriz(float**, float*, int, int);
void transcribe(FILE*, float**, float*, int, int);
int countLinhas(FILE*);
int countChars(FILE*, int);
void tiraQuebra(char*);
void setupConfig(FILE*, char**, char**, char**, int**, char**, float**, int);

/*Endif para evitar warnings*/
#endif