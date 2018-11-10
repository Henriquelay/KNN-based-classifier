/* HEADER PARA A BIBLIOTECA KNN */
#ifndef _H_KNN
#define _H_KNN
/*Aqui vai as funcoes*/
#include <stdio.h>

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
/*Endif para evitar warnings*/
#endif