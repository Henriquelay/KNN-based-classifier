/*              Esta biblioteca contém as funções
               matemáticas para utilizacao da main
               A fim de diminuir a poluição na main.

                Davi Petris e Henrique Layber                  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Início do bloco Euclides
float euclidiana(float featureTarget, float featureTraining){
    float resultado = sqrt((featureTarget - featureTraining) * (featureTarget - featureTraining));
    return resultado;
}

//implementa a distância euclidiana já como vetor
float* euclidianaVetor(float* linhaTarget, float* linhaTraining){
    float* resultado = (float*) malloc(sizeof(linhaTarget));

    if(sizeof(linhaTarget)!= sizeof(linhaTraining)){
        printf("\n\n\tFUDEU GERAL, O ARGUMENTO TEM NUMERO DE FEATURES DIFERENTE DO TREINAMENT0\n");
        exit(1);    //TODO: dar os frees antes de encerrar
    }

    for(int i = 0; i < sizeof(linhaTarget); i++)
        resultado[i] = euclidiana(linhaTarget[i], linhaTraining[i]);
    
    return resultado;
}

//implementa a distância euclidiana como vetor, como linhas de umas matriz
float** euclidianaMatriz(float** matrizTarget, float** matrizTraining){
    float** resultado = (float*) malloc(sizeof(matrizTarget));

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
