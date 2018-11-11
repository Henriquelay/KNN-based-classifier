/* HEADER PARA A BIBLIOTECA FILEMANAGER */
#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER
/*Aqui vai as funcoes*/
#include <stdio.h>


void printMatrizFile(FILE*, int, int**);
void printVetorFile(FILE*, int, float*);
void printaMatriz(float**, float*, int, int);
void transcribe(FILE*, float***, float**, int*, int*);
int countLinhas(FILE*);
int countChars(FILE*, int);
void tiraQuebra(char*);
void setupConfig(FILE*, char**, char**, char**, int**, char**, float**, int*);

/*Endif para evitar warnings*/
#endif