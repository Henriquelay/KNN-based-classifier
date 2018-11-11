/* HEADER PARA A BIBLIOTECA DE DISTANCIAS */
#ifndef _H_KNN
#define _H_KNN
/*Aqui vai as funcoes*/

struct distRot{ 
        float dist;
        float rotulo;
    };

typedef struct distRot kneigh;

void knnDist(kneigh***, float**, float*, float**, char, float, int, int, int, int);
void insortVetor(kneigh*, kneigh**, int);
void takeKNN(kneigh*, int, int, kneigh**);
float maxElem(float*, int);
float classifica(kneigh*, int, float);
void knn(float**, float*, float**, float*, float**, float*, char, int, float, int, int, int, int);


// float produtoInterno(float*, int, float*, int);
// float similaridadeCosseno(float*, int, float*, int);


/*Endif para evitar warnings*/
#endif