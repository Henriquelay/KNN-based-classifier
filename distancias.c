/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Início do bloco Euclides
float euclidiana(float featureTarget, float featureTraining){
    float resultado = (featureTarget - featureTraining) * (featureTarget - featureTraining);
    return resultado;
}

//implementa a distância euclidiana sobre um vetor
float euclidianaVetor(float* linhaTarget, float* linhaTraining){
    int i;
    float acc = 0;

    if(sizeof(linhaTarget)!= sizeof(linhaTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        exit(1);
    }

    for(i = 0; i < sizeof(linhaTarget); i++)
        acc += euclidiana(linhaTarget[i], linhaTraining[i]);
    
    float resultado = sqrt(acc);

    return resultado;
}

//implementa um vetor de euclidianaVetor
float* euclidianaMatrix(float** matrizTarget, float** matrizTraining){
    float* resultado = (float*) malloc(sizeof(matrizTarget));

    /*analizar se esse IF é de fato necessário 
    (se entradas de linhas diferentes devem ser processadas, e se sim, de que forma)*/
    if(sizeof(matrizTarget)!= sizeof(matrizTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE ENTRADAS DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < sizeof(matrizTarget); i++)
        resultado[i] = euclidianaVetor(matrizTarget[i], matrizTraining[i]);

    return resultado;
}


//Início do bloco Minkowski
float minkowski(float featureTarget, float featureTraining, float r){
    float resultado = pow(abs(featureTarget - featureTraining), r);
    return resultado;
}

//implementa Minkowski sobre um vetor
float minkowskiVetor(float* linhaTarget, float* linhaTraining, float r){
    int i;
    float acc = 0;

    if(sizeof(linhaTarget)!= sizeof(linhaTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(i = 0; i < sizeof(linhaTarget); i++)
        acc += minkowski(linhaTarget[i], linhaTraining[i], r);

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