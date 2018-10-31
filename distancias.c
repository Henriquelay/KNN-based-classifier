/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// passar checagem de entradas pra main

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

//implementa um vetor de euclidesVetor
float* euclidesMatrix(float** matrizTarget, int tamTargetRow, int tamTargetCol, float** matrizTraining, int tamTrainingRow, int tamTrainingCol){
    float* resultado = (float*) malloc(tamTrainingRow * sizeof(float));

    /*analizar se esse IF é de fato necessário 
    (se entradas de linhas diferentes devem ser processadas, e se sim, de que forma)*/
    if(tamTargetRow != tamTrainingRow){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE LINHAS DIFERENTE DO TREINAMENT0\n");
        return NULL;    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < tamTargetRow; i++)
        resultado[i] = euclidesVetor(matrizTarget[i], tamTargetCol, matrizTraining[i], tamTargetRow);

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

//implementa um vetor de minkowskiVetor
float* minkowskiMatrix(float** matrizTarget, int tamTargetRow,int tamTargetCol, float** matrizTraining, int tamTrainingRow, int tamTrainingCol, float r){
    float* resultado = (float*) malloc(tamTargetRow * sizeof(float));

    /*analizar se esse IF é de fato necessário 
    (se entradas de linhas diferentes devem ser processadas, e se sim, de que forma)*/
    if(tamTargetRow != tamTrainingRow){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE LINHAS DIFERENTE DO TREINAMENT0\n");
        return NULL;    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < tamTargetRow; i++)
        resultado[i] = minkowskiVetor(matrizTarget[i], tamTargetCol, matrizTraining[i],tamTrainingCol, r);

return resultado;
}

// distrnacia de Chebysshev aplicada em um vetor
float chebyshevVetor(float* vetorTarget, int tamTarget, float* vetorTraining, int tamTraining){
    float max = -1, atual;

    for(int i = 0; i < tamTarget; i++){
        atual = abs(vetorTarget[i] - vetorTraining[i]);
        if(atual > max) max = atual;
    }
    
    return max;
}



/* //Dependencia para a similaridadeCosseno
float produtoInterno(float* vetorA, int tamVetorA, float* vetorB, int tamVetorB){
    int i;
    float resultado = 0;
    
    if(tamVetorA != tamVetorB){
        printf("\n\n\tFUDEU GERAL, ESSES VETORES NÃO TEM PRODUTO INTERNO (TAMANHOS DIFERENTES!!)");
        return -1;
    }

    for(i = 0; i < tamVetorA; i++)
        resultado += vetorA[i] * vetorB[i];

    return resultado;
}

//Início do bloco similaridade de cosseno
float similaridadeCosseno(float* vetorTarget, int tamVetorTarget, float* vetorTraining, int TamVetorTraining){
    float resultado = produtoInterno(vetorTarget, tamVetorTarget, vetorTraining, TamVetorTraining) / euclidesVetor(vetorTarget, tamVetorTarget, vetorTraining, TamVetorTraining);
    return resultado;
} */