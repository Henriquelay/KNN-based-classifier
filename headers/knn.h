/* HEADER PARA A BIBLIOTECA KNN */
#ifndef _H_KNN
#define _H_KNN
/*Aqui vai as funcoes*/
#include <stdio.h>
#include "filemanager.h"

struct Data{
        float** matriz;
        float* rotulo;
        int nlinhas;
        int ncolunas;
};

struct Kneigh{
    float dist;
    float rotulo;
};

typedef struct Kneigh Kneigh;
typedef struct Data Data;

void knnDist(Kneigh***, Data*, Data*, Tamostra*);
void insortVetor(Kneigh*, Kneigh**, int);
void takeKNN(Kneigh*, int, int, Kneigh**);
float maxElem(float*, int);
float classifica(Kneigh*, int, float);
void knn(float**, float*, Data*, Data*, Tamostra*);

/*Endif para evitar warnings*/
#endif