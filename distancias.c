/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

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
float euclidesVetor(float* vetorTarget, float* vetorTraining){
    int i;
    float acc = 0;

    if(sizeof(vetorTarget)!= sizeof(vetorTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        exit(1);
    }

    for(i = 0; i < sizeof(vetorTarget); i++)
        acc += euclides(vetorTarget[i], vetorTraining[i]);
    
    float resultado = sqrt(acc);

    return resultado;
}

//implementa um vetor de euclidesVetor
float* euclidesMatrix(float** matrizTarget, float** matrizTraining){
    float* resultado = (float*) malloc(sizeof(matrizTarget));

    /*analizar se esse IF é de fato necessário 
    (se entradas de linhas diferentes devem ser processadas, e se sim, de que forma)*/
    if(sizeof(matrizTarget)!= sizeof(matrizTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE ENTRADAS DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < sizeof(matrizTarget); i++)
        resultado[i] = euclidesVetor(matrizTarget[i], matrizTraining[i]);

    return resultado;
}


//Início do bloco Minkowski
float minkowski(float featureTarget, float featureTraining, float r){
    float resultado = pow(abs(featureTarget - featureTraining), r);
    return resultado;
}

//implementa Minkowski sobre um vetor
float minkowskiVetor(float* vetorTarget, float* vetorTraining, float r){
    int i;
    float acc = 0;

    if(sizeof(vetorTarget)!= sizeof(vetorTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(i = 0; i < sizeof(vetorTarget); i++)
        acc += minkowski(vetorTarget[i], vetorTraining[i], r);

    float resultado = pow(acc, 1/r);

    return resultado;
}

//implementa um vetor de minkowskiVetor
float* minkowskiMatrix(float** matrizTarget, float** matrizTraining, float r){
    float* resultado = (float*) malloc(sizeof(matrizTarget));

    /*analizar se esse IF é de fato necessário 
    (se entradas de linhas diferentes devem ser processadas, e se sim, de que forma)*/
    if(sizeof(matrizTarget)!= sizeof(matrizTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE ENTRADAS DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < sizeof(matrizTarget); i++)
        resultado[i] = minkowskiVetor(matrizTarget[i], matrizTraining[i], r);
}


//Dependencia para a similaridadeCosseno
float produtoInterno(float* vetorA, float* vetorB){
    int i;
    float resultado = 0;
    
    if(sizeof(vetorA) != sizeof(vetorB)){
        printf("\n\n\tFUDEU GERAL, ESSES VETORES NÃO TEM PRODUTO INTERNO (TAMANHOS DIFERENTES!!): %i : %i\n", vetorA, vetorB);
        exit(1);
    }

    for(i = 0; i < sizeof(vetorA); i++)
        resultado += vetorA[i] * vetorB[i];

    return resultado;
}

//Início do bloco similaridade de cosseno
float similaridadeCosseno(float* vetorTarget, float* vetorTraining){
    float resultado = produtoInterno(vetorTarget, vetorTraining) / euclidesVetor(vetorTarget, vetorTraining);
    return resultado;
}