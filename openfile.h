/* HEADER PARA A BIBLIOTECA OPENFILE */
#ifndef _H_OPENFILE
#define _H_OPENFILE
/*Aqui vai as funcoes*/
#include <stdio.h>

struct Tamostra{
    int k;
    char tipoDistancia;
    float coefMinkowski;
};

struct Tpaths{
    char *pathTreino;
    char *pathTeste;
    char *pathPredicao;
};

typedef struct Tpaths Tpaths;
typedef struct Tamostra Tamostra;
typedef struct kneigh kneigh;

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
<<<<<<< HEAD
Tamostra* setupAmostras(FILE*, int);
=======
void setupAmostra(FILE*, int, Tamostra**);
>>>>>>> 9e49fbf4aec3b61927efc018242660c9a10e48d5

/*Endif para evitar warnings*/
#endif