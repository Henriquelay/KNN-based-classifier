/* HEADER PARA A BIBLIOTECA OPENFILE */
#ifndef _H_FILEMANAGER
#define _H_FILEMANAGER
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
void printaMatriz(float**, float*, int, int);
void printMatrizFile(FILE*, int, int**);
void printVetorFile(FILE*, int, float*);
void transcribe(FILE*, float***, float**, int*, int*);
int countLinhas(FILE*);
int countChars(FILE*, int);
void tiraQuebra(char*);
Tpaths* setupPaths(FILE*);
Tamostra* setupAmostras(FILE*, int);
void setupAmostra(FILE*, int, Tamostra**);

/*Endif para evitar warnings*/
#endif