/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Início do bloco Euclides
float euclides(float featureTarget, float featureTraining){
    float resultado = (featureTarget - featureTraining) * (featureTarget - featureTraining);
    return resultado;
}

//implementa a distância euclidiana sobre um vetor
float euclidesVetor(float* vetorTarget, int tamTarget, float* vetorTraining, int tamTraining){
    int i;
    float acc = 0;

    if(tamTarget != tamTraining){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        return -1;
    }

    for(i = 0; i < tamTarget; i++)
        acc += euclides(vetorTarget[i], vetorTraining[i]);
    
    float resultado = sqrt(acc);

    return resultado;
}

//Início do bloco Minkowski
float minkowski(float featureTarget, float featureTraining, float r){
    float resultado = pow(abs(featureTarget - featureTraining), r);
    return resultado;
}

//implementa Minkowski sobre um vetor (terminando a formula dele)
float minkowskiVetor(float* vetorTarget, int tamTarget, float* vetorTraining, int tamTraining, float r){
    int i;
    float acc = 0;

    if(tamTarget != tamTraining){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        return -1;    //TODO: dar os frees antes de encerrar
    }

    for(i = 0; i < tamTarget; i++)
        acc += minkowski(vetorTarget[i], vetorTraining[i], r);

    float resultado = pow(acc, 1/r);

    return resultado;
}

// distrnacia de Chebysshev aplicada em um vetor
float chernobylVetor(float* vetorTarget, int tamTarget, float* vetorTraining, int tamTraining){
    float max = -1, atual;

    for(int i = 0; i < tamTarget; i++){
        atual = sqrt((vetorTarget[i] - vetorTraining[i]) * (vetorTarget[i] - vetorTraining[i]));
        if(atual > max) max = atual;
    }
    
    return max;
}