/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/filemanager.h"
#include "../headers/distancias.h"

float absF(float num){
    if (num < 0){
        num = num * (-1);
    }

    return num;
}



//Início do bloco Euclides
float euclides(float *featureTarget, float *featureTraining){
    float resultado = (*featureTarget - *featureTraining) * (*featureTarget - *featureTraining);
    return resultado;
}

//implementa a distância euclidiana sobre um vetor
float euclidesVetor(float *vetorTarget, int *tamTarget, float *vetorTraining){
    int i;
    float acc = 0;


    for(i = 0; i < *tamTarget; i++)
        acc += euclides(&vetorTarget[i] , &vetorTraining[i]);
    
    float resultado = sqrt(acc);

    return resultado;
}

//Início do bloco Minkowski

//implementa Minkowski sobre um vetor (terminando a formula dele)
float minkowskiVetor(float *vetorTarget, int *tamTarget, float *vetorTraining, int *tamTraining, float r){
    int i;
    float dif, acc = 0;

    for(i = 0; i < *tamTarget; i++)
        dif = absF(vetorTarget[i] - vetorTraining[i]);
        acc += pow(dif, r);

    float resultado = pow(acc, 1/r);

    return resultado;
}

// distrnacia de Chebysshev aplicada em um vetor
float chernobylVetor(float **vetorTarget, int *tamTarget, float **vetorTraining, int *tamTraining){
    float max = -1, atual;

    for(int i = 0; i < *tamTarget; i++){
        atual = sqrt(((*vetorTarget)[i] - (*vetorTraining)[i]) * ((*vetorTarget)[i] - (*vetorTraining)[i]));
        if(atual > max) max = atual;
    }
    
    return max;
}